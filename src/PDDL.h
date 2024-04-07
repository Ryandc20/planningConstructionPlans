#ifndef PDDL_H
#define PDDL_H

#include <fstream>
#include <vector>

namespace fs = std::filesystem;

namespace GWEnv {
enum class Action {
  UP,
  DOWN,
  LEFT,
  RIGHT,
  FORWARD,
  BACKWARD,
  PLACE,
  REMOVE,
  NONE
};
}
class PDDL {
public:
  PDDL(fs::path filePath, bool save, bool _scaffold = false,
       bool _numerical = false);
  GWEnv::Action stepPlan();
  GWEnv::Action stepPlanNum();
  void createProblem(std::vector<std::vector<std::vector<int>>> &grid);
  void createNumProblem(std::vector<std::vector<std::vector<int>>> &grid);

private:
  void loadPlanFile();
  inline std::string adjacent(int i1, int j1, int k1, int i2, int j2, int k2);
  inline std::string position(int i, int j, int k);

  // Input file for rendering plans the pddl planner finds
  std::ifstream iFile;

  // Output file for saving problem instances to
  std::ofstream oFile;

  // Indicates whether we are using the numerical planner
  bool numerical, scaffold;
};

#endif
