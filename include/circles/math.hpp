#pragma once

#include <raylib.h>

#include <vector>

namespace circles::math {

auto sample_points(const std::vector<Vector2>& points, const std::size_t N = 512) -> std::vector<Vector2>;

}
