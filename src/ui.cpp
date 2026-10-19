#include <raylib.h>

#include <circles/ui.hpp>
#include <vector>

namespace circles::ui {

void draw() {
  InitWindow(500, 500, "Circles");
  SetTargetFPS(60);

  auto points = std::vector<Vector2>();

  while (!WindowShouldClose()) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      points.clear();
      points.push_back(GetMousePosition());
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      auto curr = GetMousePosition();
      if (points.empty()) {
        points.push_back(curr);
      } else if (points.back().x != curr.x || points.back().y != curr.y) {
        points.push_back(curr);
      }
    }

    BeginDrawing();
    ClearBackground(BLACK);

    for (std::size_t i{1}; i < points.size(); ++i) {
      DrawLineEx(points[i - 1], points[i], 2, WHITE);
    }

    EndDrawing();
  }

  CloseWindow();
}

}  // namespace circles::ui
