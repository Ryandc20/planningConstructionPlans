#include "GridWorld.h"
#include "PDDL.h"
#include "Search.h"

#include "raylib.h"
#include "rlgl.h"
#include <filesystem>
#include <iostream>
#include <memory>
#include <sstream>

using namespace std;

const int screenWidth = 1000;
const int screenHeight = 600;

void PrintError(string cmd = "") {
  if (cmd == "create") {
    cerr << "Usage ./GridWorld.h create <env_size> <file_name> <p|np>? "
            "<scaffolding>?"
            "<scaffolding>"
         << endl;
  } else if (cmd == "render") {
    cerr << "Usage ./GridWorld.h create <env_size> <file_name> <plan|building>"
         << endl;
  } else if (cmd == "search") {
    cerr << "Usage ./GridWorld.h search <env_size> <file_name>" << endl;
  } else if (cmd == "pddl") {
    cerr << "Usage ./GridWorld.h pddl <problem_file_name>" << endl;
    cerr << "Possible flag extensions\n";
    cerr << "\t --evaluator \"<specification>\" indicate what evaluator you "
            "want to use\n";
    cerr << "\t --search \"<specification>\" indicate what search algorithm "
            "you want to use\n";
    cerr << "-s include scaffolding\n";
    cerr << "-num numerical planning\n";

  } else {
    cerr << "Usage: ./GridWorld.h <create|render|search> <env_size> <file_name>"
         << endl;
  }
  exit(1);
}
int main(int argc, char *argv[]) {
  if (argc < 3)
    PrintError();

  string cmd = argv[1];

  int size = stoi(argv[2]);
  string fileName = argv[3];

  fs::path targetPaths = fs::current_path().parent_path() / "targets";
  fs::path pddlPaths = fs::current_path().parent_path() / "pddl" / fileName;
  fs::path planPaths = fs::current_path().parent_path() / "plans" / fileName;
  fs::path domainPaths = fs::current_path().parent_path() / "pddlDomains";

  bool numericalPlanning = false;
  bool scaffolding = false;
  for (int i = 0; i < argc; i++) {
    if (string(argv[i]) == "--num")
      numericalPlanning = true;
    if (string(argv[i]) == "-s")
      scaffolding = true;
  }
  cout << numericalPlanning << endl;

  shared_ptr<PDDL> pddl;

  if (cmd == "render") {
    pddl = make_shared<PDDL>(planPaths, cmd == "create", scaffolding,
                             numericalPlanning);
  } else {
    pddl = make_shared<PDDL>(pddlPaths, cmd == "create", scaffolding,
                             numericalPlanning);
  }

  GWEnv::GridWorld gridWorld(size, size, size, 2, targetPaths, true, pddl);
  if (cmd == "create") {
    InitWindow(screenWidth, screenHeight, "Grid World");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose()) {
      gridWorld.Render();
    }

  } else if (cmd == "render") {
    InitWindow(screenWidth, screenHeight, "Grid World");

    while (!WindowShouldClose()) {
      gridWorld.RenderPlan();
    }
  } else if (cmd == "search") {
    if (argc != 4)
      PrintError("search");
    // First load in the target
    // vector<vector<vector<int>>> target = gridWorld.grid;
    // Search search(scaffolding, target);

    // Try out A*
    // search.astar();

    // Try out IDA*
    // search.idastar();

    // cmake .
  } else if (cmd == "pddl") {
    if (numericalPlanning) {

    } else {
      // Call a classical planner
      stringstream cmd;

      cmd << "../planner/fast-downward.py ";

      // Get the file path to the domain file

      if (numericalPlanning) {
        if (scaffolding)
          domainPaths = domainPaths / "domainnums.pddl";
        else
          domainPaths = domainPaths / "domainnum.pddl";
      } else {
        if (scaffolding)
          domainPaths = domainPaths / "domains.pddl";
        else
          domainPaths = domainPaths / "domain.pddl";
      }

      cmd << domainPaths << ' ';

      // Get the file path to the problem file
      cmd << pddlPaths << ' ';

      cmd << " --search \"astar(ipdb())\"";

      cout << "Running command: " << cmd.str();
      system(cmd.str().c_str());

      stringstream mvCmd;

      mvCmd << "mv sas_plan " << planPaths;
      system(mvCmd.str().c_str());
    }
  } else {
    PrintError();
  }
}
