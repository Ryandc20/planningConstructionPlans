#ifndef SEARCH_H
#define SEARCH_H

#include "GridWorld.h"
#include <vector>

class Search {
public:
  Search(bool render = false);
  long long search();
  long long searchScaffold();

  GWEnv::Action stepPlan();

private:
  void savePlan();
  void neighbors();
  void neighborsScaffold();
  // Loads a goal the 3d vector containing the representation of the building to
  // build
  void loadGoal();
  // Loads a plan (sequences of actions to find the goal)
  void loadPlan();

  // Computes the heuristic
  long heuristic();

  long heuristicScaffold();

  // Computes the hash for a given state
  long hashState();

  // Stores the representation of the goal state
  std::vector<std::vector<std::vector<int>>> goal;

  std::vector<std::vector<std::vector<int>>> state;

  // Stores the found plan
  std::vector<GWEnv::Action> plan;
};
#endif
