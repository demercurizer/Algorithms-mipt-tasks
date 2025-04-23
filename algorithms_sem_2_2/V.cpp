#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

class Vertex {
 public:
  int status;
  int level;
  int index;
  int x;
  int y;

  Vertex() = default;
  Vertex(int status, int level, int index, int x, int y) {
    this->status = status;
    this->level = level;
    this->index = index;
    this->x = x;
    this->y = y;
  }
};

class Graph {
 public:
  std::vector<Vertex> vertices;
  int height;
  int length;

  void BuildGraph(const std::vector<std::vector<int>>& matrix) {
    height = static_cast<int>(matrix.size());
    length = static_cast<int>(matrix[0].size());
    int index = 0;
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < length; ++x) {
        vertices.emplace_back(Vertex(0, matrix[y][x], index, x, y));
        ++index;
      }
    }
  }

  std::vector<bool> visited;

  void BFS(int& count, int start) {
    std::queue<Vertex> q;
    q.push(vertices[start]);
    visited[start] = true;
    int additional = 0;

    while (!q.empty()) {
      Vertex v = q.front();
      int i = v.index / length;
      int j = v.index % length;
      std::vector<Vertex> neighbors;

      if (j >= 1) {
        neighbors.emplace_back(vertices[v.index - 1]);
      }
      if (i >= 1) {
        neighbors.emplace_back(vertices[v.index - length]);
      }
      if (j < length - 1) {
        neighbors.emplace_back(vertices[v.index + 1]);
      }
      if (i < height - 1) {
        neighbors.emplace_back(vertices[v.index + length]);
      }

      q.pop();

      for (const auto& neighbor : neighbors) {
        if (vertices[neighbor.index].level == v.level && !visited[neighbor.index]) {
          q.push(vertices[neighbor.index]);
          visited[neighbor.index] = true;
        }
        if (vertices[neighbor.index].level < v.level) {
          ++additional;
        }
      }

      if (q.empty() && (additional == 0)) {
        ++count;
      }
    }
  }

  int FindIsolatedAreas() {
    visited.assign(height * length, false);
    int count = 0;
    for (int i = 0; i < height * length; ++i) {
      if (!visited[i]) {
        BFS(count, i);
      }
    }
    return count;
  }
};

int main() {
  int rows, columns;
  std::cin >> rows >> columns;

  std::vector<std::vector<int>> matrix(rows);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      int value;
      std::cin >> value;
      matrix[i].push_back(value);
    }
  }

  Graph graph;
  graph.BuildGraph(matrix);

  std::cout << graph.FindIsolatedAreas();

  return 0;
}
