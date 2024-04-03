#include "PDDL.h"
#include <fstream>

using namespace GWEnv;

PDDL::PDDL(fs::path filePath, bool save) {
  if (save)
    oFileStream = new std::ofstream(filePath.c_str());
  else
    iFileStream = new std::ifstream(filePath.c_str());
}

GWEnv::Action PDDL::stepPlan() {
  // std::string line;
  // getline(*iFileStream, line);
  // GWEnv::Action action;

  // Keep getting a line until it is directly associated with an action
  if (!IsKeyPressed(KEY_ENTER))
    return Action::NONE;

  std::string line;
  if (std::getline(*iFileStream, line)) {

    if (line[0] == ';') {
      std::cout << line.substr(1) << std::endl;
      return Action::NONE;
    }
    Action action;
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
      if (zDiff > 0)
        action = Action::UP;
      if (zDiff < 0)
        action = Action::DOWN;
    }

    if (cmd == "place-column") {
      currBlockType = 1;
      return Action::PLACE;
    }

    if (cmd == "place-beam") {
      currBlockType = 2;
      return Action::PLACE;
    }

    return action;
  }

  return Action::NONE;

  return action;
}

void PDDL::createPDDLProblem(std::vector<std::vector<std::vector<int>>> grid,
                             bool scaffold) {}
void PDDL::createNumPDDLProblem(std::vector<std::vector<std::vector<int>>> grid,
                                bool scaffold) {}

std::string GridWorld::connected(std::string cmd, int i1, int j1, int k1,
                                 int i2, int j2, int k2) {
  std::stringstream adj;
  adj << "\t\t";
  adj << '(' << cmd;
  adj << " p" << i1 << "_" << j1 << "_" << k1 << " ";
  adj << "p" << i2 << "_" << j2 << "_" << k2 << ")\n";
  return adj.str();
}
