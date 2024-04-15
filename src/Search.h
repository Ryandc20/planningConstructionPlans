#ifndef SEARCH_H
#define SEARCH_H

#include "GridWorld.h"
#include <bitset>
#include <queue>
#include <unordered_map>
#include <vector>

#define ENVSIZE 5
#define BSSIZE ENVSIZE *ENVSIZE *ENVSIZE

class Search {
public:
  Search(bool scaffold, std::vector<std::vector<std::vector<int>>> goal);
  Search(bool scaffold, fs::path planFile);
  long long astar();
  long long idastar();

  GWEnv::Action stepPlan();

private:
  // Recursive (DFS) function for generating neighbors in itterative deepening
  // A*
  void search();
  void savePlan();
  std::vector<std::bitset<BSSIZE>> neighbors(std::bitset<BSSIZE> &state);
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

  // Steps through the plan to allow you to render it
  void step();

  // Construct a solution plan based on the closed list
  void constructPlan();

  std::bitset<BSSIZE> getGoal();

  std::unordered_map<std::bitset<BSSIZE>, long long> closed;

  std::priority_queue<std::pair<long long, std::bitset<BSSIZE>>> open;

  // Stores the representation of the goal state
  std::vector<std::vector<std::vector<int>>> blueprint;

  std::vector<std::vector<std::vector<int>>> state;

  // Stores the found plan
  std::vector<GWEnv::Action> plan;

  bool scaffold;
};
#endif
