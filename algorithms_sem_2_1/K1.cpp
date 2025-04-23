#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class Point {
 public:
  Point() : x(0), y(0) {
  }
  Point(const int64_t& x, const int64_t& y) : x(x), y(y) {
  }
  Point(const Point& other) : x(other.x), y(other.y) {
  }

  int64_t x;
  int64_t y;

  Point& operator=(const Point& other) = default;
};

class Vector {
 public:
  Vector() : x(0), y(0) {
  }

  Vector(const Point& a, const Point& b) : x(b.x - a.x), y(b.y - a.y) {
  }
  int64_t x;
  int64_t y;
  Vector(const Vector& other) : x(other.x), y(other.y) {
  }

  Vector& operator=(const Vector& other) = default;
};

std::istream& operator>>(std::istream& element, Point& point) {
  element >> point.x >> point.y;
  return element;
}

std::ostream& operator<<(std::ostream& element, const Point& point) {
  element << point.x << ' ' << point.y;
  return element;
}

bool operator!=(const Point& a, const Point& b) {
  return ((a.x != b.x) || (a.y != b.y));
}

Point operator-(const Point& a, const Point& b) {
  return Point(a.x - b.x, a.y - b.y);
}

Point operator+(const Point& a, const Point& b) {
  return Point(a.x + b.x, a.y + b.y);
}

bool Comp(const Point& a, const Point& b) {
  if (a.x != b.x) {
    return a.x < b.x;
  }
  return a.y < b.y;
}

int64_t operator^(const Vector& v_1, const Vector& v_2) {
  return v_1.x * v_2.y - v_2.x * v_1.y;
}

// bool operator<(const Point& p_1, const Point& p_2) {
//   Point p_0(0, 0);
//   Vector v_1(p_0, p_1);
//   Vector v_2(p_0, p_2);
//   if ((v_1 ^ v_2) != 0) {
//     return ((v_1 ^ v_2) > 0);
//   }
//   return v_1.x * v_1.x + v_1.y * v_1.y < v_2.x * v_2.x + v_2.y * v_2.y;
// }

int ShellSearch(const int& number, const std::vector<Point>& vertex, std::vector<Point>& answer) {
  answer[0] = vertex[0];
  int points_amount = 1;
  for (int i = 1; i < number; ++i) {
    while (points_amount >= 2) {
      int id = points_amount - 1;
      Vector v_1(answer[id - 1], answer[id]);
      Vector v_2(answer[id], vertex[i]);
      if ((v_1 ^ v_2) <= 0) {
        --points_amount;
      } else {
        break;
      }
    }
    answer[points_amount] = vertex[i];
    ++points_amount;
  }
  std::cout << points_amount << '\n';
  std::cout << answer[0] << '\n';
  for (int i = points_amount - 1; i > 0; --i) {
    std::cout << answer[i] << '\n';
  }
  return points_amount;
}

int64_t Area(const int& points, const std::vector<Point>& answer) {
  int64_t area = 0;
  for (int i = 0; i < points - 1; ++i) {
    area += answer[i + 1].x * answer[i].y - answer[i].x * answer[i + 1].y;
  }
  area += answer[0].x * answer[points - 1].y - answer[points - 1].x * answer[0].y;
  return std::abs(area);
}

int main() {
  int number;
  std::cin >> number;
  std::vector<Point> vertex(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> vertex[i];
  }
  std::sort(vertex.begin(), vertex.end(), Comp);
  std::vector<Point> unique_vertex(1, vertex[0]);
  for (int i = 1; i < number; ++i) {
    if (unique_vertex.back() != vertex[i]) {
      unique_vertex.push_back(vertex[i]);
    }
  }
  Point start = unique_vertex[0];
  for (int i = 1; i < unique_vertex.size(); ++i) {
    unique_vertex[i] = unique_vertex[i] - start;
  }
  std::sort(unique_vertex.begin() + 1, unique_vertex.end());
  for (int i = 1; i < unique_vertex.size(); ++i) {
    unique_vertex[i] = unique_vertex[i] + start;
  }
  std::vector<Point> answer(unique_vertex.size());
  int points_amount = ShellSearch(unique_vertex.size(), unique_vertex, answer);
  int64_t area = Area(points_amount, answer);
  if (area % 2 == 0) {
    std::cout << area / 2ll << '.' << 0;
  } else {
    std::cout << area / 2ll << '.' << 5;
  }
  return 0;
}
