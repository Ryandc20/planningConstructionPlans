#include "GridWorld.h"
#include "PDDL.h"
#include "Search.h"

#include "raylib.h"
#include "rlgl.h"
#include <filesystem>
#include <iostream>
#include <memory>

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

  fs::path targetPaths =
      fs::current_path().parent_path() / "targets" / fileName;
  fs::path pddlPaths = fs::current_path().parent_path() / "pddl" / fileName;
  fs::path planPaths = fs::current_path().parent_path() / "plans" / fileName;

  shared_ptr<PDDL> pddl = make_shared<PDDL>(pddlPaths, true);
  GWEnv::GridWorld gridWorld(size, size, size, 2, targetPaths, true, pddl);
  if (cmd == "create") {
    InitWindow(screenWidth, screenHeight, "Grid World");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose()) {
      gridWorld.Render();
    }

  } else if (cmd == "render") {
    if (argc != 5)
      PrintError("render");

    while (!WindowShouldClose()) {
      gridWorld.RenderPlan();
    }
  } else if (cmd == "search") {
    if (argc != 4)
      PrintError("search");
  } else if (cmd == "pddl") {
    // Call a classical planner
  } else {
    PrintError();
  }
}
