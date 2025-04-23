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

class Vector {
 public:
  int64_t x = 0;
  int64_t y = 0;
  Vector() = default;
  Vector(int64_t x, int64_t y) : x(x), y(y) {
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
  return std::abs(static_cast<long double>(VectorM(first, second)));
}

Vector CastINVector(const Point& first, const Point& second) {
  Vector res_vector = {second.x - first.x, second.y - first.y};
  return res_vector;
}

std::istream& operator>>(std::istream& is, Point& p) {
  is >> p.x >> p.y;
  return is;
}

struct Direct : public Vector {
  Vector direct_vector;
  explicit Direct(const Vector& direct_vector) : direct_vector(direct_vector){};
};

std::string DirectDiligence(const Vector& first, const Vector& second) {
  return VectorM(first, second) ? "NO" : "YES";
}

std::string RayDiligence(const Vector& first, const Vector& second) {
  return (VectorM(first, second) == 0 && ScalarM(first, second) >= 0) ? "YES" : "NO";
}

std::string SectionDiligence(const Vector& first, const Vector& second) {
  return (VectorM(first, second) == 0 && ScalarM(first, second) >= 0) ? "YES" : "NO";
}

long double DirectDist(const Vector& first, const Vector& second) {
  return Square(first, second) / Length(second);
}

long double RayDist(const Vector& first, const Vector& second) {
  if (ScalarM(first, second) <= 0) {
    return Length(first);
  }
  return DirectDist(first, second);
}

long double SectionDist(const Vector& first, const Vector& second, const Vector& third) {
  if (ScalarM(first, second) <= 0) {
    return Length(first);
  }
  if (ScalarM(third, second) <= 0) {
    return Length(third);
  }
  return DirectDist(first, second);
}

int main() {
  Point c;
  Point a;
  Point b;
  std::cin >> c >> a >> b;
  Vector ap = CastINVector(a, c);
  Vector pb = CastINVector(c, b);
  Vector direct_vector = CastINVector(a, b);
  std::cout << std::fixed << std::setprecision(6);
  std::cout << DirectDist(ap, direct_vector) << "\n";
  std::cout << RayDist(ap, direct_vector) << "\n";
  std::cout << SectionDist(ap, direct_vector, pb) << "\n";
  return 0;
}