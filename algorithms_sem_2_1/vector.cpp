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

int main() {
  Point p1;
  Point p2;
  Point p3;
  Point p4;
  std::cin >> p1 >> p2 >> p3 >> p4;
  Vector first = CastINVector(p1, p2);
  Vector second = CastINVector(p3, p4);
  Vector result_vector = first + second;
  std::cout << std::setprecision(6) << std::fixed << Length(first) << " " << Length(second) << "\n";
  std::cout << result_vector.x << " " << result_vector.y << "\n";
  std::cout << ScalarM(first, second) << " " << VectorM(first, second) << "\n";
  std::cout << Square(first, second) << "\n";
  return 0;
}