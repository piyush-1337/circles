#pragma once

#include <raylib.h>

#include <vector>

namespace circles::math {

struct Cycle {
  int freq;
  double radius;
  double phase;
};

auto sample_points(const std::vector<Vector2>& points, const std::size_t N = 512) -> std::vector<Vector2>;

auto dft(const std::vector<Vector2>& sampled_points) -> std::vector<Cycle>;

}
