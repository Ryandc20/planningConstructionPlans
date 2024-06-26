#include "GridWorld.h"
#include "PDDL.h"
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
  case Action::PLACECOL:
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

void GridWorld::RenderPlan() {
  if (IsCursorHidden())
    UpdateCamera(&camera, CAMERA_FREE);

  // Toggle camera controls
  if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
    if (IsCursorHidden())
      EnableCursor();
    else
      DisableCursor();
  }

  Action action = pddl->stepPlan();

  switch (action) {
  case Action::NONE:
    break;
  case Action::PLACECOL:
    currBlockType = 1;
    AddBlock(agentPos.x, agentPos.y, agentPos.z, currBlockType);
    break;
  case Action::PLACEBEAM:
    currBlockType = 2;
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

  if (IsKeyPressed(KEY_P)) {
    std::cout << "Trying to create a problem" << std::endl;
    pddl->createProblem(grid);
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
    return Action::PLACECOL;
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
