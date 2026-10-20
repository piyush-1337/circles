#include <raylib.h>

#include <circles/app.hpp>
#include <circles/math.hpp>
#include <cmath>
#include <vector>

namespace circles::app {

void run() {
  // 0, 0 is choosing the whole screen
  InitWindow(0, 0, "Circles");
  SetTargetFPS(60);

  auto width = GetScreenWidth();
  auto height = GetScreenHeight();
  auto mid = width / 2;
  auto bottom = height - 100;

  auto button = Rectangle{static_cast<float>(mid - 50),
                          static_cast<float>(bottom + 20), 100, 40};

  auto points = std::vector<Vector2>();
  auto sampled = std::vector<Vector2>();

  bool is_drawing{false};
  bool is_simulating{false};

  auto cycles = std::vector<math::Cycle>();
  auto time = double{};
  std::vector<Vector2> trail;

  while (!WindowShouldClose()) {
    auto mouse_pos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      if (mouse_pos.x < mid && mouse_pos.y < bottom) {
        is_drawing = true;
        is_simulating = false;

        points.clear();
        sampled.clear();

        points.push_back(mouse_pos);
      } else if (CheckCollisionPointRec(mouse_pos, button)) {
        if (!is_simulating && points.size() > 1) {
          is_drawing = false;
          is_simulating = true;

          points.push_back(points[0]);
          sampled = math::sample_points(points);

          for (auto& p : sampled) p.x += mid;

          cycles = math::dft(sampled);

          time = 0;
          trail.clear();
        }
      }
    }

    if (is_drawing && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      if (mouse_pos.x < mid && mouse_pos.y < bottom) {
        if (points.back().x != mouse_pos.x || points.back().y != mouse_pos.y) {
          points.push_back(mouse_pos);
        }
      }
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      is_drawing = false;
    }

    BeginDrawing();
    ClearBackground(BLACK);

    DrawLine(mid, 0, mid, bottom, WHITE);       // vertical line
    DrawLine(0, bottom, width, bottom, WHITE);  // horizontal line
    DrawRectangleLinesEx(button, 2, WHITE);     // simulate button
    DrawText("Simulate", mid - 25, bottom + 35, 12,
             WHITE);  // simulate text on the button

    for (std::size_t i{1}; i < points.size(); ++i) {
      DrawLineEx(points[i - 1], points[i], 2, WHITE);
    }

    if (is_simulating) {
      Vector2 pos{0, 0};

      for (const auto& cycle : cycles) {
        const Vector2 prev = pos;
        const auto angle = cycle.phase + time * cycle.freq;

        pos.x += cycle.radius * std::cos(angle);
        pos.y += cycle.radius * std::sin(angle);

        if (cycle.freq == 0) continue;

        DrawCircleLinesV(prev, cycle.radius, GRAY);
        DrawLineV(prev, pos, WHITE);
      }

      trail.push_back(pos);

      for (std::size_t i{1}; i < trail.size(); ++i) {
        DrawLineEx(trail[i - 1], trail[i], 2, RED);
      }

      time += 2.0 * std::numbers::pi / static_cast<double>(cycles.size());

      if (time >= 2.0 * std::numbers::pi) {
        time = 0.0;
        trail.clear();
      }
    }

    EndDrawing();
  }

  CloseWindow();
}

}  // namespace circles::app
