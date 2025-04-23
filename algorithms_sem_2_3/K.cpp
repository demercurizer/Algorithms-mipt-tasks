#include <iostream>
#include <vector>
#include <algorithm>

namespace constants {
const int kInfinity = 1000000000;
}

class Edge {
 public:
  int from;
  int to;
  int weight;
  Edge() = default;

  Edge(int start, int end, int w) : from(start), to(end), weight(w) {
  }
};

// Функция для инициализации массива расстояний и предшественников
void InitializeDistances(int num_vertices, std::vector<int>& distances, std::vector<int>& predecessors) {
  distances.assign(num_vertices, constants::kInfinity);
  distances[0] = 0;
  predecessors.assign(num_vertices, -1);
}

// Функция для релаксации рёбер графа
void RelaxEdges(int num_vertices, const std::vector<Edge>& edges, std::vector<int>& distances,
                std::vector<int>& predecessors) {
  for (int i = 0; i < num_vertices - 1; ++i) {
    for (const auto& edge : edges) {
      if (distances[edge.from] != constants::kInfinity && distances[edge.to] > distances[edge.from] + edge.weight) {
        distances[edge.to] = std::max(distances[edge.from] + edge.weight, -constants::kInfinity);
        predecessors[edge.to] = edge.from;
      }
    }
  }
}

// Функция для поиска отрицательного цикла в графе
bool FindNegativeCycle(int num_vertices, const std::vector<Edge>& edges, const std::vector<int>& distances,
                       std::vector<int>& predecessors, std::vector<int>& cycle) {
  for (const auto& edge : edges) {
    if (distances[edge.from] != constants::kInfinity && distances[edge.to] > distances[edge.from] + edge.weight) {
      int cycle_start = edge.to;
      for (int i = 0; i < num_vertices; ++i) {
        cycle_start = predecessors[cycle_start];
      }
      for (int v = cycle_start;; v = predecessors[v]) {
        cycle.push_back(v);
        if (v == cycle_start && cycle.size() > 1) {
          break;
        }
      }
      std::reverse(cycle.begin(), cycle.end());
      return true;
    }
  }
  return false;
}

// Основная функция для запуска алгоритма Беллмана-Форда
void BellmanFord(int num_vertices, const std::vector<Edge>& edges) {
  std::vector<int> distances;
  std::vector<int> predecessors;

  InitializeDistances(num_vertices, distances, predecessors);
  RelaxEdges(num_vertices, edges, distances, predecessors);

  std::vector<int> cycle;
  if (FindNegativeCycle(num_vertices, edges, distances, predecessors, cycle)) {
    std::cout << "YES\n";
    std::cout << cycle.size() << '\n';
    for (const auto& vertex : cycle) {
      std::cout << vertex + 1 << ' ';
    }
    std::cout << '\n';
  } else {
    std::cout << "NO\n";
  }
}

// Основная функция для чтения входных данных и запуска алгоритма
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int num_vertices;
  std::cin >> num_vertices = 0;
  std::vector<Edge> edges;

  for (int i = 0; i < num_vertices; ++i) {
    for (int j = 0; j < num_vertices; ++j) {
      int weight = 0;
      std::cin >> weight;
      if (weight != 100000) {
        edges.emplace_back(i, j, weight);
      }
    }
  }

  BellmanFord(num_vertices, edges);
  return 0;
}
