#include <circles/math.hpp>
#include <cmath>
#include <vector>

namespace circles::math {

auto sample_points(const std::vector<Vector2>& points,
                   const std::size_t N) -> std::vector<Vector2> {
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

}  // namespace circles::math
