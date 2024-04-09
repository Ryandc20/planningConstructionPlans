#include "PDDL.h"
#include "raylib.h"
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>

using namespace GWEnv;

PDDL::PDDL(fs::path filePath, bool save, bool _scaffold, bool _numerical) {
  numerical = _numerical;
  _scaffold = _scaffold;
  if (save)
    oFile.open((filePath.c_str()));
  else if (std::filesystem::exists(filePath))
    iFile.open(filePath.c_str(), std::ios::out);
  else
    exit(1);
}

GWEnv::Action PDDL::stepPlan() {
  Action action = Action::NONE;

  // Only want to get the next step of the plan if the enter key is being
  // pressed
  if (!IsKeyPressed(KEY_ENTER))
    return action;

  // Get a line from the plan file
  std::string line;
  getline(iFile, line);

  return action;
}

void PDDL::createProblem(std::vector<std::vector<std::vector<int>>> &grid) {
  if (numerical) {
    createNumProblem(grid);
    return;
  }
  oFile << "(define (problem 1)\n";
  oFile << "\t(:domain cubeworld)\n\n";

  // Define the objects
  oFile << "\t(:objects ";
  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[0].size(); j++) {
      oFile << "\n\t\t";
      for (size_t k = 0; k < grid[0][0].size(); k++) {
        oFile << position(i, j, k) << ' ';
      }
    }
  }
  oFile << "\n\t)\n\n";

  // Define the initial state
  oFile << "\t(:init\n";

  // Define what blocks are adjacent from one another
  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[0].size(); j++) {
      for (size_t k = 0; k < grid[0][0].size(); k++) {
        if (i > 0)
          oFile << adjacent(i, j, k, i - 1, j, k);
        if (i < grid.size() - 1)
          oFile << adjacent(i, j, k, i + 1, j, k);
        if (j > 0)
          oFile << adjacent(i, j, k, i, j - 1, k);
        if (j < grid[0].size() - 1)
          oFile << adjacent(i, j, k, i, j + 1, k);
        if (k > 0)
          oFile << adjacent(i, j, k, i, j, k - 1);
        if (k < grid[0][0].size() - 1)
          oFile << adjacent(i, j, k, i, j, k + 1);
      }
    }
  }

  // Define the needs columns and beam predicates
  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[0].size(); j++) {
      for (size_t k = 0; k < grid[0][0].size(); k++) {
        // Needs a column
        if (grid[i][j][k] == 1) {
          oFile << "\t\t(ncolumn " << position(i, j, k) << ")\n";
        }

        // Needs a beam
        if (grid[i][j][k] == 2) {
          oFile << "\t\t(nbeam " << position(i, j, k) << ")\n";
        }

        // Does that block need to have scaffold associated with it
        if ((grid[i][j][k] == 1 or grid[i][j][k] == 2) and scaffold and i > 0) {
          // Left scaffold
          if (j > 0)
            oFile << scaffoldT(i, j, k, i - 1, j - 1, k);

          // Right scaffold
          if (j < grid[0].size() - 1)
            oFile << scaffoldT(i, j, k, i - 1, j + 1, k);

          // Backward scaffold
          if (k > 0)
            oFile << scaffoldT(i, j, k, i - 1, j, k - 1);

          // Forward scaffold
          if (k < grid[0][0].size() - 1)
            oFile << scaffoldT(i, j, k, i - 1, j, k + 1);
        }
      }
    }
  }
  oFile << ")\n";

  // Define the goal state
  oFile << "\t(goal:\n";
  oFile << "\t\t(and\n";
  // Make sure all the columns are completed
  oFile << "\t\t\tcolumns-completed\n";

  // Make sure all the beams are completed

  oFile << "\t\t\t(forall (?pos - position)";
  oFile << "\t\t\t\t(or (and (nbeam ?pos) (beam ?pos)) (and (not (nbeam ?pos)) "
           "(not (beam ?pos))))\n";
  oFile << "\t\t\t)\n";

  // Make sure the scaffold is all completed
  if (scaffold) {
    oFile << "\t\t\t(forall (?pos - position)\n";
    oFile << "\t\t\t\t(not (scaffold ?pos))\n";
    oFile << "\t\t\t)\n";
  }

  oFile << "\t\t)\b";
  oFile << "\t)\n";
  oFile << ")\n";

  oFile.close();
}

void PDDL::createNumProblem(std::vector<std::vector<std::vector<int>>> &grid) {}

inline std::string PDDL::adjacent(int i1, int j1, int k1, int i2, int j2,
                                  int k2) {
  std::stringstream adj;
  adj << "\t\t";
  adj << '(' << "adjacent ";
  adj << position(i1, j1, k1) << ' ';
  adj << position(i2, j2, k2) << ")\n";
  return adj.str();
}

inline std::string PDDL::position(int i, int j, int k) {
  std::stringstream pos;
  pos << "p" << i << '_' << j << '_' << k;
  return pos.str();
}

inline std::string PDDL::scaffoldT(int i1, int j1, int k1, int i2, int j2,
                                   int k2) {
  std::stringstream cmd;
  cmd << "\t\t";
  cmd << '(' << "scaffold";
  cmd << position(i1, j1, k1) << ' ';
  cmd << position(i2, j2, k2) << ")\n";
  return cmd.str();
}
