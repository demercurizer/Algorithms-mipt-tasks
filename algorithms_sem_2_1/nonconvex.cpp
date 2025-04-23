#include <iostream>
#include <cmath>
#include <istream>
#include <iomanip>

struct Point {
  int64_t x = 0;
  int64_t y = 0;
  Point() = default;
  Point(int64_t x, int64_t y) : x(x), y(y) {
  }

  friend std::istream& operator>>(std::istream& is, Point& p);
};

class Vector : public Point {
 public:
  Vector() = default;
  Vector(int64_t x, int64_t y) : Point(x, y) {
  }

  friend Vector operator+(const Vector& first, const Vector& second);
  friend Vector CastINVector(const Point& first, const Point& second);
  friend long double Length(const Vector& current);
  friend long double Square(const Vector& first, const Vector& second);
  friend int64_t ScalarM(const Vector& first, const Vector& second);
  friend int64_t VectorM(const Vector& first, const Vector& second);
};

Vector operator+(const Vector& first, const Vector& second) {
  Vector result = {first.x + second.x, first.y + second.y};
  return result;
}

long double Length(const Vector& current) {
  long double result = std::sqrt(current.x * current.x + current.y * current.y);
  return result;
}

int64_t ScalarM(const Vector& first, const Vector& second) {
  int64_t result = first.x * second.x + first.y * second.y;
  return result;
}

int64_t VectorM(const Vector& first, const Vector& second) {
  int64_t result = first.x * second.y - first.y * second.x;
  return result;
}

long double Square(const Vector& first, const Vector& second) {
  return 0.5 * std::abs(static_cast<long double>(VectorM(first, second)));
}

Vector CastINVector(const Point& first, const Point& second) {
  Vector res_vector = {second.x - first.x, second.y - first.y};
  return res_vector;
}

std::istream& operator>>(std::istream& is, Point& p) {
  is >> p.x >> p.y;
  return is;
}

std::string CheckConvex(const auto& arr, const int& n) {
  int64_t idol = 0;
  int idx = 0;
  while (idol == 0 && idx + 2 < n) {
    idol = VectorM(CastINVector(arr[idx], arr[idx + 1]), CastINVector(arr[idx + 1], arr[idx + 2]));
    ++idx;
  }
  idol /= std::abs(idol);
  for (int i = idx; i < n - 2; ++i) {
    Vector first = CastINVector(arr[i], arr[i + 1]);
    Vector second = CastINVector(arr[i + 1], arr[i + 2]);
    if (idol * VectorM(first, second) < 0) {
      return "NO";
    }
  }
  return "YES";
}

int main() {
  int n = 0;
  std::cin >> n;
  auto* arr = new Point[n + 2];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  arr[n] = arr[0];
  arr[n + 1] = arr[1];
  std::cout << CheckConvex(arr, n + 2) << "\n";
  delete[] arr;
  return 0;
}