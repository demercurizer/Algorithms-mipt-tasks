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

long double Square(int64_t n, const auto* arr) {
  __uint128_t result_plus = 0;
  __uint128_t result_minus = 0;
  __uint128_t result  = 0;  
  for (int i = 1; i <= n; ++i) {
    result = arr[i].x * (arr[i + 1].y - arr[i - 1].y);
    if (result > 0) {
      result_plus += result;
    } else {
      result_minus += -result;
    }
    if(result_minus >= result_plus) {
      result_minus -= result_plus;
      result_plus = 0;
    } else {
      result_plus -= result_minus;
      result_minus = 0;
    }
  }
  result = result_minus - result_plus;
  return std::abs(static_cast<long double>(result)) / 2;
}


int main() {
  int n = 0;
  std::cin >> n;
  auto* arr = new Point[n + 2];
  for (int i = 1; i < n + 1; ++i) {
    std::cin >> arr[i];
  }
  arr[0] = arr[n];
  arr[n + 1] = arr[1];
  std::cout << Square(n, arr) << "\n";
  delete[] arr;
  return 0;
}