#include "GridWorld.h"
#include "raylib.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

namespace GWEnv {

void GridWorld::Draw(bool instructions) const {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  BeginMode3D(camera);

  DrawPlanes();
  DrawBlocks();

  EndMode3D();

  if (instructions) {
    DrawRectangle(10, 10, 240, 150, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(10, 10, 240, 150, BLUE);

    DrawText(IsCursorHidden() ? "Mode: Free camera - right click to switch"
                              : "Mode: Fixed Camera - right click to switch",
             20, 20, 10, BLACK);
    DrawText("WASD: Horizontal move", 40, 40, 10, DARKGRAY);
    DrawText("QE: Vertical move", 40, 60, 10, DARKGRAY);
    DrawText("X: Delete block", 40, 80, 10, DARKGRAY);
    DrawText("SPACE: Place block", 40, 100, 10, DARKGRAY);
    DrawText("ENTER: Save to file", 40, 120, 10, DARKGRAY);

    DrawRectangle(900, 10, 70, 70, Fade(blockColors[currBlockType], 0.5f));
    DrawRectangleLines(900, 10, 70, 70, blockColors[currBlockType]);
    DrawText("Block type", 910, 20, 10, DARKGRAY);
    DrawText(std::to_string(currBlockType).c_str(), 930, 35, 20, DARKGRAY);
  }

  EndDrawing();
}

void GridWorld::Render() {
  if (IsCursorHidden())
    UpdateCamera(&camera, CAMERA_FREE);

  // Toggle camera controls
  if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
    if (IsCursorHidden())
      EnableCursor();
    else
      DisableCursor();
  }
  Action action = Step();
  switch (action) {
  case Action::NONE:
    break;
  case Action::PLACE:
    AddBlock(agentPos.x, agentPos.y, agentPos.z, currBlockType);
    break;
  case Action::REMOVE:
    RemoveBlock(agentPos.x, agentPos.y, agentPos.z);
    break;
  default:
    Move(action);
    break;
  }

  // Draw the screen
  Draw(true);
}

void GridWorld::RenderPlan(std::ifstream &file) {
  if (IsCursorHidden())
    UpdateCamera(&camera, CAMERA_FREE);

  // Toggle camera controls
  if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
    if (IsCursorHidden())
      EnableCursor();
    else
      DisableCursor();
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  Action action = stepPDDLPlan(file);

  switch (action) {
  case Action::NONE:
    break;
  case Action::PLACE:
    AddBlock(agentPos.x, agentPos.y, agentPos.z, currBlockType);
    break;
  case Action::REMOVE:
    RemoveBlock(agentPos.x, agentPos.y, agentPos.z);
    break;
  default:
    Move(action);
    break;
  }

  // Draw the screen
  Draw(false);
}

void GridWorld::DrawPlanes() const {
  float hLength = (float)h * spacing;
  float wLength = (float)w * spacing;
  float dLength = (float)d * spacing;

  rlBegin(RL_LINES);
  for (int i = 0; i <= h; i++) {
    float lineOffset = (float)i * spacing;
    rlColor3f(0.25f, 0.25f, 1.0f);
    rlVertex3f(lineOffset, 0.0f, 0.0f);
    rlVertex3f(lineOffset, wLength, 0.0f);

    rlColor3f(1.0f, 0.25f, 0.25f);
    rlVertex3f(lineOffset, 0.0f, 0.0f);
    rlVertex3f(lineOffset, 0.0f, dLength);
  }

  for (int i = 0; i <= w; i++) {
    float lineOffset = (float)i * spacing;
    rlColor3f(0.25f, 0.25f, 1.0f);
    rlVertex3f(0.0f, lineOffset, 0.0f);
    rlVertex3f(hLength, lineOffset, 0.0f);

    rlColor3f(0.25f, 1.0f, 0.25f);
    rlVertex3f(0.0f, lineOffset, 0.0f);
    rlVertex3f(0.0f, lineOffset, dLength);
  }

  for (int i = 0; i <= d; i++) {
    float lineOffset = (float)i * spacing;
    rlColor3f(1.0f, 0.25f, 0.25f);
    rlVertex3f(0.0f, 0.0f, lineOffset);
    rlVertex3f(hLength, 0.0f, lineOffset);

    rlColor3f(0.25f, 1.0f, 0.25f);
    rlVertex3f(0.0f, 0.0f, lineOffset);
    rlVertex3f(0.0f, wLength, lineOffset);
  }

  rlEnd();
}

bool GridWorld::AddBlock(int x, int y, int z, int blockType) {
  if (x >= h || y >= w || z >= d || grid[x][y][z] == blockType ||
      !QueryPlacement(x, y, z))
    return false;

  grid[x][y][z] = blockType;
  return true;
}

void GridWorld::Move(Action direction) {
  switch (direction) {
  case Action::RIGHT:
    agentPos.x = std::min(w - 1, agentPos.x + 1);
    break;
  case Action::LEFT:
    agentPos.x = std::max(0, agentPos.x - 1);
    break;
  case Action::DOWN:
    agentPos.y = std::max(0, agentPos.y - 1);
    break;
  case Action::UP:
    agentPos.y = std::min(h - 1, agentPos.y + 1);
    break;
  case Action::BACKWARD:
    agentPos.z = std::min(d - 1, agentPos.z + 1);
    break;
  case Action::FORWARD:
    agentPos.z = std::max(0, agentPos.z - 1);
    break;
  default:
    break;
  }
}

bool GridWorld::QueryPlacement(int x, int y, int z) const {
  if (y == 0)
    return true;
  if ((x > 0 && grid[x - 1][y][z]) || (x < h - 1 && grid[x + 1][y][z]))
    return true;

  else if ((y > 0 && grid[x][y - 1][z]) || (y < w - 1 && grid[x][y + 1][z]))
    return true;

  else if ((z > 0 && grid[x][y][z - 1]) || (z < d - 1 && grid[x][y][z + 1]))
    return true;

  return false;
}

void GridWorld::DrawBlocks() const {
  // Draw every block in grid
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      for (int k = 0; k < d; k++) {
        if (grid[i][j][k]) {
          float posX = static_cast<float>(i) * spacing + 0.5f;
          float posY = static_cast<float>(j) * spacing + 0.5f;
          float posZ = static_cast<float>(k) * spacing + 0.5f;

          DrawCube({posX, posY, posZ}, spacing, spacing, spacing,
                   Fade(blockColors[grid[i][j][k]], 0.5f));
          DrawCubeWires({posX, posY, posZ}, spacing, spacing, spacing, RED);
        }
      }
    }
  }

  // Draw current agent position
  DrawCubeWires({static_cast<float>(agentPos.x) * spacing + 0.5f,
                 static_cast<float>(agentPos.y) * spacing + 0.5f,
                 static_cast<float>(agentPos.z) * spacing + 0.5f},
                spacing, spacing, spacing, PURPLE);
}

void GridWorld::RemoveBlock(int x, int y, int z) { grid[x][y][z] = 0; }

void GridWorld::ResizeGrid(uint32_t _w, uint32_t _h, uint32_t _d) {
  grid = {_w, vec<vec<int>>(_h, vec<int>(_d, 0))};
  agentPos = {0, 0, 0};
}

/* Trying out binary format. Sorry Thanh
void GridWorld::SaveToFile() const {
    std::ofstream myfile;
    myfile.open(filePath, std::fstream::out);

    for (int i=0; i < w; i++) {
        for (int j=0; j < d; j++) {
            for (int k=0; k < h; k++) {
                myfile << grid[i][j][k] << " ";
            }
            myfile << std::endl;
        }
        myfile << std::endl;
    }
    myfile << std::endl;
    myfile.close();
}
*/

void GridWorld::SaveToFile() const {
  std::cout << "Saving to file" << std::endl;
  size_t size = w * d * h + 3;
  std::unique_ptr<int[]> flatArray = std::make_unique<int[]>(size);
  flatArray[0] = w;
  flatArray[1] = h;
  flatArray[2] = d;

  size_t index = 3;

  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      for (int k = 0; k < d; k++) {
        flatArray[index++] = grid[i][j][k];
      }
    }
  }

  std::ofstream file(filePath, std::ios_base::binary);
  file.write((char *)flatArray.get(),
             static_cast<std::streamsize>(size * sizeof(int)));
  file.close();
}

Action GridWorld::Step() {
  // Do not allow save file if nothing changes
  static bool enterDelayed = false;

  // C-style enums lmao :) hope raylib doesn't change this.
  for (int i = 1; i <= nBlockTypes; i++) {
    if (IsKeyPressed(i + KEY_ZERO)) {
      currBlockType = i;
      return Action::NONE;
    }
  }

  if (IsKeyPressed(KEY_ENTER)) {
    if (enterDelayed)
      return Action::NONE;
    enterDelayed = true;

    SaveToFile();
    return Action::NONE;
  }

  // Save to pddl
  if (IsKeyPressed(KEY_P)) {
    if (enterDelayed)
      return Action::NONE;
    enterDelayed = true;

    SaveToPDDL("test");
    return Action::NONE;
  }

  // A little hack to avoid setting enterDelayed = true in every if statement
  bool prevDelayedStatus = enterDelayed;
  enterDelayed = false;

  if (IsCursorHidden())
    return Action::NONE;

  if (IsKeyPressed(KEY_W))
    return Action::FORWARD;
  if (IsKeyPressed(KEY_S))
    return Action::BACKWARD;
  if (IsKeyPressed(KEY_A))
    return Action::LEFT;
  if (IsKeyPressed(KEY_D))
    return Action::RIGHT;
  if (IsKeyPressed(KEY_UP))
    return Action::UP;
  if (IsKeyPressed(KEY_DOWN))
    return Action::DOWN;

  if (IsKeyPressed(KEY_SPACE)) {
    enterDelayed = false;
    return Action::PLACE;
  }
  if (IsKeyPressed(KEY_X)) {
    enterDelayed = false;
    return Action::REMOVE;
  }

  return Action::NONE;
}

void GridWorld::LoadFromFile() {
  if (!fs::exists(filePath)) {
    std::cerr << "File " << filePath << " does not exist" << std::endl;
    exit(1);
  }

  std::ifstream file(filePath, std::ios_base::binary);
  int x, y, z;
  file.read((char *)&x, sizeof(int));
  file.read((char *)&y, sizeof(int));
  file.read((char *)&z, sizeof(int));
  if (x != w || y != h || z != d)
    ResizeGrid(x, y, z);

  // Could read directly into grid instead of array. Not sure which way is more
  // efficient
  std::unique_ptr<int[]> flatArray = std::make_unique<int[]>(x * y * z);
  file.read((char *)flatArray.get(),
            static_cast<std::streamsize>(x * y * z * sizeof(int)));
  size_t index = 0;

  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      for (int k = 0; k < d; k++) {
        grid[i][j][k] = flatArray[index++];
      }
    }
  }
  file.close();
}

void GridWorld::SaveToPDDL(std::string problemName) const {
  std::cout << "Creating pddl files" << std::endl;
  createPDDLDomain(problemName);
  createPDDLProblem(problemName);
}

void GridWorld::createPDDLDomain(std::string problemName) const {
  // Open up the template
  //
}

void GridWorld::createPDDLProblem(std::string problemName) const {
  std::ofstream file(filePath);

  // Add the start of the file template
  file << "(define (problem " << problemName << ")\n";
  file << "\t(:domain cubeworld)\n";

  // Define the objects
  file << "\t(:objects\n";

  file << "\t\t";
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      for (int k = 0; k < d; k++)
        file << "p" << i << "_" << j << "_" << k << " ";
    }
  }
  file << "- position\n";
  file << "\t)\n\n";

  // Define the initial state
  file << "\t(:init\n";

  // Create the starting location for the agent
  file << "\t\t(at-agent p0_0_0)\n";
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < d; j++) {
      for (int k = 0; k < h; k++) {
        // Adjacent to left block
        if (i > 0)
          file << connected("adjacent", i, j, k, i - 1, j, k);

        // Adjacent to right block
        if (i < w - 1)
          file << connected("adjacent", i, j, k, i + 1, j, k);

        // Adjacent to backward block
        if (j > 0)
          file << connected("adjacent", i, j, k, i, j - 1, k);

        // Adjacent to forward block
        if (j < h - 1)
          file << connected("adjacent", i, j, k, i, j + 1, k);

        // Adjacent to downward block
        if (k > 0)
          file << connected("adjacent", i, j, k, i, j, k - 1);

        // Adjacent to upward block
        if (k < d - 1)
          file << connected("adjacent", i, j, k, i, j, k + 1);
      }
    }
  }

  // Add what blocks are on the floor
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < d; j++) {
      file << "\t\t(on-floor ";
      file << "p" << i << '_' << j << "_0)\n";
    }
  }

  for (int i = 0; i < w; i++) {
    for (int j = 0; j < d; j++) {
      for (int k = 0; k < h; k++) {
        if (k > 0) {
        }
      }
    }
  }
  // Add the scafold needed
  file << "\t)\n\n";

  // Define the goal state
  file << "\t(:goal (and\n";

  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      for (int k = 0; k < d; k++) {
        if (grid[i][j][k]) {
          file << "\t\t(full p" << i << "_" << k << "_" << j << ")\n";
        } else {
          file << "\t\t(not (full p" << i << "_" << k << "_" << j << "))\n";
        }
      }
    }
  }

  file << "\t))\n";
  file << ")\n";

  file.close();
}

// Performs the next action in the PDDL file plan
Action GridWorld::stepPDDLPlan(std::ifstream &file) {
  if (!IsKeyPressed(KEY_ENTER))
    return Action::NONE;

  std::string line;
  if (std::getline(file, line)) {

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
}

std::string GridWorld::connected(std::string cmd, int i1, int j1, int k1,
                                 int i2, int j2, int k2) {
  std::stringstream adj;
  adj << "\t\t";
  adj << '(' << cmd;
  adj << " p" << i1 << "_" << j1 << "_" << k1 << " ";
  adj << "p" << i2 << "_" << j2 << "_" << k2 << ")\n";
  return adj.str();
}

} // namespace GWEnv
