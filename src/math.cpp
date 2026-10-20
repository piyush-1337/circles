#include <algorithm>
#include <circles/math.hpp>
#include <cmath>
#include <numbers>
#include <vector>

namespace circles::math {

auto sample_points(const std::vector<Vector2>& points, const std::size_t N)
    -> std::vector<Vector2> {
  if (points.size() < 2) return points;

  auto total_len = double{0};
  for (std::size_t i{1}; i < points.size(); ++i) {
    total_len += std::hypot(points[i - 1].x - points[i].x,
                            points[i - 1].y - points[i].y);
  }

  const auto step = total_len / static_cast<double>(N);

  auto res = std::vector<Vector2>();
  res.reserve(N);
  res.push_back(points[0]);

  auto sum = double{0};
  for (std::size_t i{1}; i < points.size(); ++i) {
    double ax = points[i - 1].x;
    double ay = points[i - 1].y;
    const double bx = points[i].x;
    const double by = points[i].y;

    double d = std::hypot(bx - ax, by - ay);

    while (sum + d >= step && res.size() < N) {
      const double need = step - sum;

      const double unit_x = (bx - ax) / d;
      const double unit_y = (by - ay) / d;

      ax += need * unit_x;
      ay += need * unit_y;

      res.push_back(Vector2{
          static_cast<float>(ax),
          static_cast<float>(ay),
      });

      d -= need;
      sum = 0.0;
    }

    sum += d;
  }

  return res;
}

auto dft(const std::vector<Vector2>& sampled_points) -> std::vector<Cycle> {
  const auto N = static_cast<int>(sampled_points.size());

  const auto low_freq = -(N / 2);
  const auto high_freq = N - (N / 2);

  auto res = std::vector<Cycle>();
  res.reserve(N);

  for (auto k = low_freq; k < high_freq; ++k) {
    auto re = double{0.0};
    auto im = double{0.0};

    for (int i{}; i < N; ++i) {
      auto x = sampled_points[i].x;
      auto y = sampled_points[i].y;

      auto theta = (2 * std::numbers::pi * k * i) / static_cast<double>(N);

      re += x * std::cos(theta) + y * std::sin(theta);
      im += y * std::cos(theta) - x * std::sin(theta);
    }

    re /= static_cast<double>(N);
    im /= static_cast<double>(N);

    const auto radius = std::hypot(re, im);
    const auto phase = std::atan2(im, re);

    res.push_back(
        {.freq = static_cast<int>(k), .radius = radius, .phase = phase});
  }

  std::ranges::sort(res, [](const Cycle& a, const Cycle& b) {
    if (a.freq == 0 || b.freq == 0) return a.freq == 0 && b.freq != 0;
    return a.radius > b.radius;
  });

  return res;
}

}  // namespace circles::math
