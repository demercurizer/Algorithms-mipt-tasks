#include <iostream>
#include <cmath>
#include <istream>
#include <iomanip>
#include <algorithm>
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

bool SectionDiligence(const Vector& first, const Vector& second) {
  bool result = VectorM(first, second) == 0 && ScalarM(first, second) >= 0;
  return result;
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

std::string IntersectionSegments(const Point& inf_idol, const auto* arr, const Point& idol, int n) {
  int64_t intersection = 0;
  Point a = idol;
  Point b = inf_idol;
  Vector ab = CastINVector(a, b);
  for (int i = 0; i < n - 1; ++i) {
    Point c = arr[i];
    Point d = arr[i + 1];
    Vector ac = CastINVector(a, c);
    Vector ad = CastINVector(a, d);
    Vector cd = CastINVector(c, d);
    Vector ca = CastINVector(c, a);
    Vector cb = CastINVector(c, b);

    if (SectionDiligence(ca, ad)) {
      return "YES";
    }

    if (VectorM(ab, ac) * VectorM(ab, ad) <= 0 && VectorM(cd, ca) * VectorM(cd, cb) <= 0) {
      ++intersection;
    }
  }
  return intersection % 2 ? "YES" : "NO";
}

int main() {
  int n = 0;
  Point idol;
  std::cin >> n >> idol.x >> idol.y;
  Point inf_idol{idol.x + 1, 100000};
  auto* arr = new Point[n + 1];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  arr[n] = arr[0];
  std::cout << IntersectionSegments(inf_idol, arr, idol, n + 1) << "\n";
  delete[] arr;
  return 0;
}