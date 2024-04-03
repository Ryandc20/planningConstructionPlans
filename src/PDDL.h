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
  PDDL(fs::path filePath, bool save);
  GWEnv::Action stepPlan();
  GWEnv::Action stepPlanNum();
  void createPDDLProblem(std::vector<std::vector<std::vector<int>>> grid,
                         bool scaffold);
  void createNumPDDLProblem(std::vector<std::vector<std::vector<int>>> grid,
                            bool scaffold);

private:
  void loadPlanFile();
  std::string connected(std::string cmd, int i1, int j1, int k1, int i2, int j2,
                        int k2);
  std::ifstream iFile;
  std::ofstream oFile;
};

#endif
