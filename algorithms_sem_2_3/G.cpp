#include <iostream>
#include <vector>

class Edge {
 public:
  int v1 = 0;
  int v2 = 0;
  int weight = 0;

  Edge() = default;
  Edge(int u, int v, int w) : v1(u), v2(v), weight(w) {
  }
};

std::istream& operator>>(std::istream& is, Edge& edge) {
  is >> edge.v1 >> edge.v2 >> edge.weight;
  --edge.v1;
  --edge.v2;
  return is;
}

namespace constants {
constexpr int kInf = 30000;
}

class Graph {
 public:
  int vertex_count;
  std::vector<Edge> edges;

  explicit Graph(int vertices, int edge_count) : vertex_count(vertices) {
    edges.reserve(edge_count);
  }

  void AddEdge(int u, int v, int weight) {
    edges.emplace_back(u, v, weight);
  }

  void FordBellman(int start) {
    std::vector<int> dist(vertex_count, constants::kInf);
    dist[start] = 0;

    for (int i = 0; i < vertex_count - 1; ++i) {
      for (const auto& edge : edges) {
        if (dist[edge.v1] != constants::kInf && dist[edge.v2] > dist[edge.v1] + edge.weight) {
          dist[edge.v2] = dist[edge.v1] + edge.weight;
        }
      }
    }

    for (int i = 0; i < vertex_count; ++i) {
      if (dist[i] == constants::kInf) {
        std::cout << constants::kInf << ' ';
      } else {
        std::cout << dist[i] << ' ';
      }
    }
    std::cout << '\n';
  }
};

int main() {
  int vertex_count = 0;
  int edge_count = 0;
  std::cin >> vertex_count >> edge_count;

  Graph graph(vertex_count, edge_count);

  for (int i = 0; i < edge_count; ++i) {
    Edge edge;
    std::cin >> edge;
    graph.AddEdge(edge.v1, edge.v2, edge.weight);
  }

  graph.FordBellman(0);
  return 0;
}
