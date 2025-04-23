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
template <class T>
std::string IntersectionSegments(T& ab, T& ac, T& ad, T& cd, T& ca, T& cb, T& bd, T& db) {
  if (VectorM(ab, ac) == 0 && VectorM(ab, ad) == 0 && VectorM(cd, ca) == 0 && VectorM(cd, cb) == 0) {
    bool result =
        SectionDiligence(ac, cb) || SectionDiligence(ad, db) || SectionDiligence(ca, ad) || SectionDiligence(cb, bd);
    return result ? "YES" : "NO";
  }
  if (VectorM(ab, ac) * VectorM(ab, ad) <= 0 && VectorM(cd, ca) * VectorM(cd, cb) <= 0) {
    return "YES";
  }
  return "NO";
}

template <class T>
long double SegmentsDistance(T& ab, T& ac, T& ad, T& cd, T& ca, T& cb, T& bd, T& db) {
  if (IntersectionSegments(ab, ac, ad, cd, ca, cb, bd, db) == "YES") {
    return 0;
  }
  long double first_comp = std::min(SectionDist(ac, ab, cb), SectionDist(ad, ab, db));
  long double second_comp = std::min(SectionDist(ca, cd, ad), SectionDist(cb, cd, bd));
  return std::min(first_comp, second_comp);
}
int main() {
  Point c;
  Point a;
  Point b;
  Point d;
  std::cin >> a >> b >> c >> d;
  Vector ab = CastINVector(a, b);
  Vector ac = CastINVector(a, c);
  Vector ad = CastINVector(a, d);
  Vector cd = CastINVector(c, d);
  Vector ca = CastINVector(c, a);
  Vector cb = CastINVector(c, b);
  Vector bd = CastINVector(b, d);
  Vector db = CastINVector(d, b);
  std::cout << std::fixed << std::setprecision(6);
  std::cout << SegmentsDistance(ab, ac, ad, cd, ca, cb, bd, db) << "\n";
  return 0;
}