#include <cmath>
#include <iomanip>
#include <iostream>
#include <istream>
#include <utility>

struct Point {
  long double x = 0;
  long double y = 0;
  Point() = default;
  Point(long double x, long double y) : x(x), y(y) {
  }

  friend std::istream& operator>>(std::istream& is, Point& p);
};

class Vector {
 public:
  long double x = 0;
  long double y = 0;
  Vector() = default;
  Vector(long double x, long double y) : x(x), y(y) {
  }

  friend Vector operator+(const Vector& first, const Vector& second);
  friend Vector CastINVector(const Point& first, const Point& second);
  friend long double Length(const Vector& current);
  friend long double Square(const Vector& first, const Vector& second);
  friend long double ScalarM(const Vector& first, const Vector& second);
  friend long double VectorM(const Vector& first, const Vector& second);
};

struct Direct : public Vector {
  long double a = 0;
  long double b = 0;
  long double c = 0;
  Direct(int a, int b, int c) : a(a), b(b), c(c) {
  }
  Direct() = default;
  Vector direct_vector{};

  friend std::istream& operator>>(std::istream& is, Point& p);
  long double Dist(const Direct& first, const Direct& second);
  Vector Intersection(const Direct& first, const Direct& second);
};

Vector operator+(const Vector& first, const Vector& second) {
  Vector result = {first.x + second.x, first.y + second.y};
  return result;
}

long double Length(const Vector& current) {
  long double result = std::sqrt(current.x * current.x + current.y * current.y);
  return result;
}

long double ScalarM(const Vector& first, const Vector& second) {
  long double result = first.x * second.x + first.y * second.y;
  return result;
}

long double VectorM(const Vector& first, const Vector& second) {
  long double result = first.x * second.y - first.y * second.x;
  return result;
}

long double Square(const Vector& first, const Vector& second) {
  return 0.5 * std::abs((VectorM(first, second)));
}

Vector CastINVector(const Point& first, const Point& second) {
  Vector res_vector = {second.x - first.x, second.y - first.y};
  return res_vector;
}

std::istream& operator>>(std::istream& is, Point& p) {
  is >> p.x >> p.y;
  return is;
}

std::istream& operator>>(std::istream& is, Direct& direct) {
  is >> direct.a >> direct.b >> direct.c;
  direct.direct_vector.x = direct.b;
  direct.direct_vector.y = -direct.a;
  return is;
};

long double Dist(const Direct& first, const Direct& second) {
  if (first.a * second.b == first.b * second.a) {
    if (first.a != 0) {
      long double result =
          std::abs(second.a * (-first.c / first.a) + second.c) / std::sqrt(second.a * second.a + second.b * second.b);
      return result;
    }
    long double result =
        std::abs(second.b * (-first.c / first.b) + second.c) / std::sqrt(second.a * second.a + second.b * second.b);
    return result;
  }
  return 0;
}

std::pair<long double, long double> Intersection(const Direct& first, const Direct& second) {
  long double det = first.a * second.b - first.b * second.a;
  long double det_x = -first.c * second.b + first.b * second.c;
  long double det_y = -first.a * second.c + first.c * second.a;
  std::pair<long double, long double> result = {det_x / (det_x == .0 ? 1 : det), det_y / (det_y == .0 ? 1 : det)};
  return result;
}
bool Check(const Direct& first, const Direct& second) {
  return (first.a * second.b == first.b * second.a) && (first.c * second.a == second.c * first.a);
}
int main() {
  Direct first;
  Direct second;

  std::cin >> first;
  std::cin >> second;
  std::cout << std::fixed << std::setprecision(6);
  std::cout << first.direct_vector.x << " " << first.direct_vector.y << "\n";
  std::cout << second.direct_vector.x << " " << second.direct_vector.y << "\n";
  if (Dist(first, second) != 0 || Check(first, second)) {
    std::cout << Dist(first, second) << "\n";
  } else {
    std::cout << Intersection(first, second).first << " " << Intersection(first, second).second << "\n";
  }
  return 0;
}