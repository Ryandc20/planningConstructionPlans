#include "GridWorld.h"
#include "PDDL.h"
#include "Search.h"

#include "raylib.h"
#include "rlgl.h"
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;

void PrintError(string cmd = nullptr) {
  if (cmd == "create") {
    cerr << "Usage ./GridWorld.h create <env_size> <file_name> <p|np|s>? "
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

  int size = stoi(argv[1]);
  string fileName = argv[2];

  fs::path targetPaths = fs::current_path().parent_path() / "targets";
  fs::path pddlPaths = fs::current_path().parent_path() / "pddl";
  fs::path planPaths = fs::current_path().parent_path() / "plans";

  if (cmd == "create") {
  } else if (cmd == "render") {
    if (argc != 5)
      PrintError("render");
  } else if (cmd == "search") {
    if (argc != 4)
      PrintError("search");
  } else if (cmd == "pddl") {
  } else {
    PrintError();
  }
}
