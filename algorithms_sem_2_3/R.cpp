#include <iostream>
#include <vector>
#include <algorithm>

class Graph {
 public:
  class Edge {
   public:
    int64_t v1;
    int64_t v2;
    int64_t tin;
    int64_t tup;

    Edge() : v1(0), v2(0), tin(0), tup(0) {
    }
    Edge(int64_t v1, int64_t v2, int64_t tin, int64_t tup) : v1(v1), v2(v2), tin(tin), tup(tup) {
    }

    friend std::istream& operator>>(std::istream& is, Edge& edge) {
      is >> edge.v1 >> edge.tin >> edge.v2 >> edge.tup;
      --edge.v1;
      --edge.v2;
      return is;
    }
  };

  int64_t vertex_count;
  std::vector<Edge> edges;

  explicit Graph(int64_t vertex_count) : vertex_count(vertex_count) {
  }

  void AddEdge(const Edge& edge) {
    edges.push_back(edge);
  }

  int64_t FordBalman(int64_t start, int64_t finish) {
    std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) {
      if (e1.tin != e2.tin) {
        return e1.tin > e2.tin;
      }
      if (e1.v1 != e2.v1) {
        return e1.v1 < e2.v1;
      }
      if (e1.v2 != e2.v2) {
        return e1.v2 < e2.v2;
      }
      return e1.tup < e2.tup;
    });

    const int64_t k_inf = 1e18;
    std::vector<int64_t> dist(vertex_count, k_inf);
    dist[start] = 0;

    for (int64_t vertex = 0; vertex < vertex_count; ++vertex) {
      for (const auto& edge : edges) {
        if (dist[edge.v1] != k_inf && dist[edge.v2] > edge.tup && dist[edge.v1] <= edge.tin) {
          dist[edge.v2] = edge.tup;
        }
      }
    }

    return dist[finish];
  }
};

int main() {
  int64_t vertex_count = 0;
  int64_t start = 0;
  int64_t finish = 0;
  int64_t edge_count = 0;

  std::cin >> vertex_count;
  std::cin >> start >> finish;
  --start;
  --finish;
  std::cin >> edge_count;

  Graph graph(vertex_count);
  for (int64_t i = 0; i < edge_count; ++i) {
    Graph::Edge edge;
    std::cin >> edge;
    graph.AddEdge(edge);
  }

  std::cout << graph.FordBalman(start, finish);
  return 0;
}
