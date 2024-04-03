#ifndef PDDL_H
#define PDDL_H

#include "GridWorld.h"
#include <filesystem>
#include <vector>

class PDDL {
public:
  PDDL(fs::path filePath, bool save);
  GWEnv::Action stepPlan();
  void createPDDLProblem(std::vector<std::vector<std::vector<int>>> grid,
                         bool scaffold);
  void createNumPDDLProblem(bool scaffold = false);

private:
  void loadPlanFile();
  std::ifstream *iFileStream = nullptr;
  std::ofstream *oFileStream = nullptr;
};

#endif
