#include "Search.h"
#include "PDDL.h"
#include <bitset>

typedef long long ll;

// For the implementation we are assuming the memory requirnment is not to bad

using namespace std;
using namespace GWEnv;

GWEnv::Action action;

Search::Search(bool _scaffold, vector<vector<vector<int>>> goal)
    : scaffold(_scaffold) {}

Search::Search(bool _scaffold, fs::path planPath) : scaffold(_scaffold) {}

ll Search::astar() {
  // Get the goal node
  bitset<BSSIZE> goal = getGoal();

  ll cost;
  bitset<BSSIZE> node;
  while (open.size()) {
    // Get the current node
    cost = open.top().first;
    node = open.top().second;

    // Check if the current node is the goal
    if (goal == node) {
      constructPlan();
      return cost;
    }

    for (auto n : neighbors(node)) {
      // Check if this state has not been visited before
      // Do not need to check for shorter paths as
      if (true) {
        // Compute the heurstic for this node for the cost need to go until you
        // reach the goal
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
        goal.set(idx, true);
      }
    }
  }

  return goal;
}

ll Search::idastar() { search(); }

// Does the recursive part of the IDA* search
void Search::search() {}

// Save the plan in text so the sequences of actions can be represented
void Search::savePlan() {}

// Generates the neighbor states
std::vector<std::bitset<BSSIZE>> Search::neighbors(bitset<BSSIZE> &state) {}

// Load the goal state actually this will probably be done be the grid world
// class
void Search::loadGoal() {}

// Loads in a plan
void Search::loadPlan() {}

// Compute the heuristic of the cost left to go
long Search::heuristic() { return 0.; }

long Search::heuristicScaffold() { return 0.; }

// Probably not needed anymore
long Search::hashState() { return 0.; }

// Will Recursively look through the closed list to construct the sequence
// of actions to perform to build the structure
void Search::constructPlan() {}

Action Search::stepPlan() { return Action::NONE; }
