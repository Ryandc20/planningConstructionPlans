#include "PDDL.h"
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>

using namespace GWEnv;

PDDL::PDDL(fs::path filePath, bool save) {

  if (save)
    oFile.open((filePath.c_str()));
  else if (std::filesystem::exists(filePath))
    iFile.open(filePath.c_str(), std::ios::out);
  else
    exit(1);
}

GWEnv::Action PDDL::stepPlan() {
  std::string line;
  getline(iFile, line);
  GWEnv::Action action;

  return action;
}

void PDDL::createPDDLProblem(std::vector<std::vector<std::vector<int>>> grid,
                             bool scaffold) {

  int w, d, h;
  w = d = h = grid.size();

  oFile << "(define (problem 1 )\n";
  oFile << "\t(:domain cubeworld)\n";

  // Define the objects
  oFile << "\t(:objects\n";

  oFile << "\t\t";
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      for (int k = 0; k < d; k++)
        oFile << "p" << i << "_" << j << "_" << k << " ";
    }
  }
  oFile << "- position\n";
  oFile << "\t)\n\n";

  // Define the initial state
  oFile << "\t(:init\n";

  // Create the starting location for the agent
  oFile << "\t\t(at-agent p0_0_0)\n";
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < d; j++) {
      for (int k = 0; k < h; k++) {
        // Adjacent to left block
        if (i > 0)
          oFile << connected("adjacent", i, j, k, i - 1, j, k);

        // Adjacent to right block
        if (i < w - 1)
          oFile << connected("adjacent", i, j, k, i + 1, j, k);

        // Adjacent to backward block
        if (j > 0)
          oFile << connected("adjacent", i, j, k, i, j - 1, k);

        // Adjacent to forward block
        if (j < h - 1)
          oFile << connected("adjacent", i, j, k, i, j + 1, k);

        // Adjacent to downward block
        if (k > 0)
          oFile << connected("adjacent", i, j, k, i, j, k - 1);

        // Adjacent to upward block
        if (k < d - 1)
          oFile << connected("adjacent", i, j, k, i, j, k + 1);
      }
    }
  }

  // Add what blocks are on the floor
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < d; j++) {
      oFile << "\t\t(on-floor ";
      oFile << "p" << i << '_' << j << "_0)\n";
    }
  }

  oFile << "\t))\n";
  oFile << ")\n";

  oFile.close();
}

void PDDL::createNumPDDLProblem(std::vector<std::vector<std::vector<int>>> grid,
                                bool scaffold) {

  oFile.close();
}

std::string PDDL::connected(std::string cmd, int i1, int j1, int k1, int i2,
                            int j2, int k2) {
  std::stringstream adj;
  adj << "\t\t";
  adj << '(' << cmd;
  adj << " p" << i1 << "_" << j1 << "_" << k1 << " ";
  adj << "p" << i2 << "_" << j2 << "_" << k2 << ")\n";
  return adj.str();
}
