#include "Search.h"
#include "PDDL.h"
#include <bitset>

typedef long long ll;

// For the implementation we are assuming the memory requirnment is not to bad

using namespace std;
using namespace GWEnv;

GWEnv::Action action;

// Constructer when using the search algorithm to find a path
Search::Search(bool _scaffold, vector<vector<vector<int>>> _goal)
    : scaffold(_scaffold), goal(_goal) {
  goalBit = getGoal();
}

// Constructer when loading in a path to render a plan
Search::Search(bool _scaffold, fs::path planPath) : scaffold(_scaffold) {}

ll Search::astar() {
  uint32_t f, g;
  State state;
  while (open.size()) {
    // Get the current node
    f = open.top().first;
    state = open.top().second;

    // Check if the current node is the goal
    if (goalBit == state.first) {
      constructPlan();
      savePlan();
      return f;
    }

    Node *nodeCurr = &closed[state];
    for (auto [n, action] : neighbours(state)) {
      // Compute the cost of the neighbor node
      g = nodeCurr->g + 1;

      f = g + heuristic(n);
      // Check if this state has not been visited before
      // Do not need to check for shorter paths as
      if (closed.count(n) != 0) {
        // Add the nodes to the closed list
        closed[n] = {f, g, n, action, nodeCurr};

        // Add the node to the open list
        open.push({f, n});
      }

      // If we have already encounter this node in the search
      if (closed[n].f > f) {

        open.push({f, n});
      }
    }
  }

  // There does not exists a solution to this problem
  return -1;
}

// Gets the goal based on the environment in the since it converts the array
// into a bitset
bitset<BSSIZE> Search::getGoal() {
  bitset<BSSIZE> goal(0);
  int idx = 0;
  for (int i = 0; i < blueprint.size(); i++) {
    for (int j = 0; j < blueprint[0].size(); j++) {
      for (int k = 0; k < blueprint[0][0].size(); k++) {
        if (blueprint[i][j][k])
          goal.set(idx, true);
        idx++;
      }
    }
  }

  return goal;
}

// Implementation of itterative deeping A*
ll Search::idastar() { search(); }

// Does the recursive part of the IDA* search
void Search::search() {}

// Save the plan in text so the sequences of actions can be represented
void Search::savePlan() {}

// Generates the neighbor states
vector<pair<State, Action>> Search::neighbours(State &state) {
  vector<pair<State, Action>> n;
  uint16_t agent_location = state.first;
  auto stateBitSet = state.second;

  // Get the xyz values that agent_location represents
  uint16_t x = agent_location % ENVSIZE;
  uint16_t y = agent_location / ENVSIZE % ENVSIZE;
  uint16_t z = agent_location / (ENVSIZE * ENVSIZE) % ENVSIZE;

  // Check if the standard moves are possible there are no blocks in the way
  uint16_t left_location = agent_location - 1;
  uint16_t right_location = agent_location + 1;
  uint16_t forward_location = agent_location + ENVSIZE;
  uint16_t backward_location = agent_location - ENVSIZE;
  uint16_t up_location = agent_location + ENVSIZE * ENVSIZE;
  uint16_t down_location = agent_location - ENVSIZE * ENVSIZE;

  // Can we move left ?
  if (!state.second[left_location] and x > 0)
    n.push_back({{left_location, stateBitSet}, Action::LEFT});

  // Can we move right ?
  if (!state.second[right_location] and x < ENVSIZE - 1)
    n.push_back({{right_location, stateBitSet}, Action::RIGHT});

  // Can we move forward ?
  if (!state.second[forward_location] and y > 0)
    n.push_back({{forward_location, stateBitSet}, Action::FORWARD});

  // Can we move backward ?
  if (!state.second[backward_location] and y < ENVSIZE - 1)
    n.push_back({{backward_location, stateBitSet}, Action::BACKWARD});

  // Can we move up ?
  if (!state.second[up_location] and z > 0)
    n.push_back({{up_location, stateBitSet}, Action::UP});

  // Can we move down ?
  if (!state.second[down_location] and z < ENVSIZE - 1)
    n.push_back({{down_location, stateBitSet}, Action::DOWN});

  // If there is already a block here don't want to keep placing blocks here
  if (stateBitSet[state.first])
    return n;

  // Set the block to true
  stateBitSet[state.first] = true;

  // Check if we can place a column
  if (!beamTime and goal[x][y][z] == 1) {
    // Make sure there is adjacent block or that it is sitting on the floor
    n.push_back({{agent_location, stateBitSet}, Action::PLACECOL});
  }

  // Check if we can place a beam
  if (beamTime and goal[x][y][z] == 2) {
    // Mkae sure there is adjacent block or that it is sitting on the floor
    n.push_back({{agent_location, stateBitSet}, Action::PLACEBEAM});
  }

  // Check if we can place a scaffold
  if (scaffold) {
  }
  return n;
}

// Loads in a plan
void Search::loadPlan() {}

// Compute the heuristic of the cost left to go
uint32_t Search::heuristic(State &state) {
  uint32_t h = 0;

  uint16_t agent_location = state.first;
  auto stateBitset = state.second;

  uint32_t blocks = 0;

  // Some black magic hackery
  auto needs_placed = stateBitset & goalBit;

  // Count how many blocks left to place
  for (size_t i = 0; i < BSSIZE; i++) {
    blocks += needs_placed[i];
  }

  while (blocks--) {
    // Find the nearset block add the distance to the heuristic cost + 1 for the
    // effort to place that block. To do so I am going to need bfs
    auto [loc, length] = bitSetBFS(state);
    h += 1 + length;

    // Set the agent location to that block
    agent_location = loc;

    // Remove that block from needs placed
    needs_placed[agent_location] = false;
  }
  return h;
}

std::pair<uint32_t, uint32_t> Search::bitSetBFS(State state) {

  // Could not find a block
  return {-1, -1};
}

long Search::heuristicScaffold() { return 0.; }

// Will Recursively look through the closed list to construct the sequence
// of actions to perform to build the structure
void Search::constructPlan() { savePlan(); }

Action Search::stepPlan() { return Action::NONE; }
