#include "GridWorld.h"
#include "raylib.h"
#include "rlgl.h"
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;

// void PrintError() {
//   std::cerr << "Usage: ./GridWorldEnv <env_size> <num_block_types> <s|l> "
//                "<file_name>\n\n"
//             << "<env_size>       : size of the environment\n"
//             << "<num_block_types>: number of block types\n"
//             << "<s|l|p>          : whether to save to file, load from file or
//             "
//                "load from plan\n"
//             << "<file_name>      : path to file to load from / save to\n";
//
//   exit(1);
// }

void PrintError(string cmd = nullptr) {
  if (cmd == "create") {

  } else if (cmd == "render") {

  } else if (cmd == "search") {

  } else {
    cerr << "Usage: ./GridWorld.h <create|render|search> ..." << endl;
  }
  exit(1);
}
int main(int argc, char *argv[]) {
  if (argc < 2)
    PrintError();

  string cmd = argv[1];

  if (cmd == "create") {
    if (argc != 4)
      PrintError();

    int size = stoi(argv[1]);
    string fileName = argv[3];

  } else if (cmd == "render") {
  } else if (cmd == "search") {

  } else {
  }
}

// int main(int argc, char *argv[]) {
//   for (int i = 0; i < argc; i++) {
//     std::cout << argv[i] << " ";
//   }
//   std::cout << argc << std::endl;
//
//   if (argc != 5)
//     PrintError();
//
//   int size = std::stoi(argv[1]);
//   int blockTypes = std::stoi(argv[2]);
//
//   if (blockTypes > 13) {
//     std::cerr << "Support for more than 13 block types not supported yet";
//     exit(1);
//   }
//
//   std::string operation{argv[3]};
//   if (operation != "s" and operation != "l" and operation != "p")
//     PrintError();
//   bool save = operation == "s" or operation == "p";
//
//   fs::path pddlPaths = fs::current_path().parent_path() / "pddl";
//   fs::path plansPaths = fs::current_path().parent_path() / "plans";
//
//   // Check if the directory exists
//   if (!fs::exists(pddlPaths)) {
//     // Directory does not exist, create it
//     if (!fs::create_directories(pddlPaths)) {
//       std::cerr << "Failed to create directory: " << pddlPaths << std::endl;
//       return 1;
//     }
//   }
//
//   fs::path filePathPDDL = pddlPaths / argv[4];
//   fs::path filePathPlans;
//
//   const int screenWidth = 1920;
//   const int screenHeight = 1080;
//
//   GWEnv::GridWorld env(size, size, size, blockTypes,
//   pddlPaths.generic_string(),
//                        save);
//   InitWindow(screenWidth, screenHeight, "Grid World");
//
//   SetTargetFPS(60); // Set our game to run at 60 frames-per-second
//
//   if (operation == "s" or operation == "l") {
//     // Main game loop
//     while (!WindowShouldClose()) // Detect window close button or ESC key
//     {
//       env.Render();
//     }
//
//   } else {
//     std::ifstream planFile(pddlPaths);
//     while (!WindowShouldClose()) {
//       env.RenderPlan(planFile);
//     }
//   }
//   CloseWindow(); // Close window and OpenGL context
//
//   return 0;
// }
