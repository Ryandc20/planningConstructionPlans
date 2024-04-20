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
  scaffold = _scaffold;
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

  if (std::getline(iFile, line)) {
    std::cout << line << std::endl;

    if (line[0] == ';') {
      std::cout << line.substr(1) << std::endl;
      return action;
    }
    // Remove the parentheses
    line = line.substr(1, line.size() - 1);

    std::istringstream lineStream(line);

    std::string cmd;

    lineStream >> cmd;

    if (cmd == "move-agent") {
      std::string from, to;
      lineStream >> from;
      lineStream >> to;

      int x1, x2, y1, y2, z1, z2;

      // Remove the p which is in front of the block locations
      from = from.substr(1);
      to = to.substr(1);

      // Warning some wacky code follows
      for (char &ch : from)
        if (ch == '_')
          ch = ' ';
      for (char &ch : to)
        if (ch == '_')
          ch = ' ';
      std::istringstream fromStream(from);
      std::istringstream toStream(to);
      fromStream >> x1 >> y1 >> z1;
      toStream >> x2 >> y2 >> z2;

      // Figure out the direction in one position does the value differ
      int xDiff = x2 - x1, yDiff = y2 - y1, zDiff = z2 - z1;

      // The first two need to be reversed from forward to bacward because we
      // start at a position where we can only move backward
      if (xDiff > 0)
        action = Action::BACKWARD;
      if (xDiff < 0)
        action = Action::FORWARD;
      if (yDiff > 0)
        action = Action::RIGHT;
      if (yDiff < 0)
        action = Action::LEFT;
      if (zDiff > 0) {
        action = Action::UP;
      }
      if (zDiff < 0)
        action = Action::DOWN;
    }

    if (cmd == "place-column")
      action = Action::PLACECOL;

    if (cmd == "place-beam")
      action = Action::PLACEBEAM;
  }
  return action;
}

void PDDL::createProblem(std::vector<std::vector<std::vector<int>>> &grid) {
  std::cout << "Creating file\n";
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
      oFile << " - position";
    }
  }
  oFile << "\n\t)\n\n";

  // Define the initial state
  oFile << "\t(:init\n";

  // Count the number of beams and columns
  int numBeams = 0, numCols = 0;
  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[0].size(); j++) {
      for (size_t k = 0; k < grid[0][0].size(); k++) {
        if (grid[i][j][k] == 1)
          numCols++;
        if (grid[i][j][k] == 2)
          numBeams++;
      }
    }
  }

  if (numerical) {
    oFile << "\t\t(= (num-col " << numCols << "))\n";
    oFile << "\t\t(= (num-beam " << numCols << "))\n";
    if (scaffold)
      oFile << "\t\t(= (num-scaffold) 0)\n";
  }

  oFile << "\t\t(at-agent p0_0_0)\n";

  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      oFile << "\t\t(on-floor " << position(i, j, 0) << ")\n";
    }
  }

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
          oFile << "\t\t(ncolumn " << position(i, k, j) << ")\n";
        }

        // Needs a beam
        if (grid[i][j][k] == 2) {
          oFile << "\t\t(nbeam " << position(i, k, j) << ")\n";
        }

        // Does that block need to have scaffold associated with it
        if ((grid[i][j][k] == 1 or grid[i][j][k] == 2) and scaffold and k > 0) {
          // Left scaffold
          if (i > 0)
            oFile << scaffoldT(i, j, k, i - 1, j, k - 1);

          // Right scaffold
          if (i < grid[0].size() - 1)
            oFile << scaffoldT(i, j, k, i + 1, j, k - 1);

          // Backward scaffold
          if (j > 0)
            oFile << scaffoldT(i, j, k, i, j - 1, k - 1);

          // Forward scaffold
          if (j < grid[0][0].size() - 1)
            oFile << scaffoldT(i, j, k, i, j + 1, k - 1);
        }
      }
    }
  }
  oFile << "\t)\n";

  // Define the goal state
  oFile << "\t(:goal\n";
  oFile << "\t\t(and\n";

  if (numerical) {

    oFile << "\t\t\t (= (num-col) 0)\n";
    oFile << "\t\t\t (= (num-beam) 0)\n";
    if (scaffold)
      oFile << "\t\t\t (= (num-scaffold) 0)\n";
  } else {
    for (int i = 0; i < grid.size(); i++) {
      for (int j = 0; j < grid[0].size(); j++) {
        for (int k = 0; k < grid[0][0].size(); k++) {
          if (grid[i][j][k] == 1)
            oFile << "\t\t\t(column " << position(i, k, j) << " )\n";
          if (grid[i][j][k] == 2)
            oFile << "\t\t\t(beam " << position(i, k, j) << ")\n";
        }
      }
    }
  }

  oFile << "\t\t)\n";
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
