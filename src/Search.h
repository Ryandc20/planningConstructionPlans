// #ifndef SEARCH_H
// #define SEARCH_H
//
// #include "GridWorld.h"
// #include <bitset>
// #include <queue>
// #include <unordered_map>
// #include <vector>
//
// #define ENVSIZE 5
// #define BSSIZE ENVSIZE *ENVSIZE *ENVSIZE
//
// // Represents a single state in the environemnt
// typedef std::pair<uint16_t, std::bitset<BSSIZE>> State;
//
// using namespace GWEnv;
//
// // Represents a search Node only for use in close list
// // open list just needs to store the total cost and the State representation
// to
// // hash
// struct Node {
//   // g: the cost to current node
//   // f: total cost f = g + h (heuristic value)
//   uint32_t f, g;
//   State state;
//   Action action;
//   Node *parent = nullptr;
// };
//
// class Search {
// public:
//   Search(bool scaffold, std::vector<std::vector<std::vector<int>>> goal);
//   Search(bool scaffold, fs::path planFile);
//   long long astar();
//   long long idastar();
//
//   GWEnv::Action stepPlan();
//
// private:
//   // Recursive (DFS) function for generating neighbors in itterative
//   deepening
//   // A*
//   void search();
//   void savePlan();
//   std::vector<std::pair<State, Action>> neighbours(State &state);
//   void neighborsScaffold();
//   // Loads a goal the 3d vector containing the representation of the building
//   to
//   // build
//   void loadGoal();
//   // Loads a plan (sequences of actions to find the goal)
//   void loadPlan();
//
//   // Computes the heuristic
//   uint32_t heuristic(State &state);
//
//   // Computes the heuristic probably going to be the same as scaffold
//   long heuristicScaffold();
//
//   // Steps through the plan to allow you to render it
//   void step();
//
//   // Construct a solution plan based on the closed list
//   void constructPlan();
//
//   // Returns the location and cost of the closest node
//   std::pair<uint32_t, uint32_t> bitSetBFS(State state);
//
//   std::bitset<BSSIZE> getGoal();
//
//   // Closed list information
//   std::unordered_map<State, Node> closed;
//
//   // Open list information
//   std::priority_queue<std::pair<uint32_t, State>> open;
//
//   // Stores the representation of the goal state
//   std::vector<std::vector<std::vector<int>>> blueprint;
//
//   // Stores the found plan
//   std::vector<GWEnv::Action> plan;
//
//   std::vector<std::vector<std::vector<int>>> goal;
//
//   // Don't care where the agent is for the goal
//   std::bitset<BSSIZE> goalBit;
//
//   bool scaffold;
//
//   bool beamTime = false;
// };
// #endif
