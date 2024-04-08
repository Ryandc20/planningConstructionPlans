#include "Search.h"
#include "PDDL.h"
#include <bitset>

typedef long long ll;

// For the implementation we are assuming the memory requirnment is not to bad

using namespace std;

GWEnv::Action action;

Search::Search(bool _render, bool _scaffold) {
  // If we are rendering a plan we need to open the file
}

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
      // Check if this state has been visited before
    }
  }

  // There does not exists a solution to this problem
  return -1;
}

// Gets the goal based on the environment
bitset<BSSIZE> Search::getGoal() {
  bitset<BSSIZE> goal;
  for (int i = 0; i < blueprint.size(); i++) {
    for (int j = 0; j < blueprint[0].size(); j++) {
      for (int k = 0; k < blueprint[0][0].size(); k++) {
      }
    }
  }

  return goal;
}

ll Search::idastar() { search(); }

ll Search::search() {}

void Search::savePlan() {}

// Generates the neighbor states
void Search::neighbors(bitset<BSSIZE> &state) {}

void Search::loadGoal() {}

void Search::loadPlan() {}

long Search::heuristic() { return 0.; }

long Search::heuristicScaffold() { return 0.; }

long Search::hashState() { return 0.; }

void Search::constructPlan() {}
