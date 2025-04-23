#include <iostream>
#include <vector>
#include <queue>

struct Point {
  int x = 0;
  int y = 0;
  int value = 0;
  Point() = default;
  Point(int x, int y, int value) : x(x), y(y), value(value) {
  }
};

int BFS(const Point& begin, const std::vector<Point>& graph, int n, int m) {
  std::vector<int> dist(n * m, -1);
  std::queue<int> queue;
  std::vector<bool> used;
  queue.(begin.x * m + begin.y);
  dist[begin.x * m + begin.y] = 0;
  while (!queue.empty()) {
    int v = queue.front();
    queue.pop();
    std::vector<int> neighbors{-1, -1, -1, -1};
    int x = v / m;
    int y = v % m;
    if (x > 0) {
      neighbors[0] = (x - 1) * m + y;
    }
    if (x < n - 1) {
      neighbors[1] = (x + 1) * m + y;
    }
    if (y > 0) {
      neighbors[2] = x * m + y - 1;
    }
    if (y < m - 1) {
      neighbors[3] = x * m + y + 1;
    }
    for (int neighbor : neighbors) {
      if (neighbor < 0 || neighbor >= n * m || dist[neighbor] != -1) {
        continue;
      }
      if (!used[neighbor]) {
        dist[neighbor] = dist[v] + 1;
        if (graph[neighbor].value == 1) {
          return dist[neighbor];
        }
        queue.push(neighbor);
        used[neighbor] = true;
      }
    }
  }
  return 0;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<Point> graph(n * m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int value = 0;
      std::cin >> value;
      graph[i * m + j] = Point(i, j, value);
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (graph[i * m + j].value != 1) {
        std::cout << BFS(graph[i * m + j], graph, n, m) << " ";
      } else {
        std::cout << 0 << " ";
      }
    }
    std::cout << "\n";
  }
}
