#include <algorithm>
#include <iostream>
#include <vector>

class Edge {
 public:
  int v1 = 0;
  int v2 = 0;
  int weight = 0;

  Edge() = default;

  Edge(int first, int second, int w) : v1(first), v2(second), weight(w) {
  }
};

bool operator<(const Edge& e1, const Edge& e2) {
  return e1.weight < e2.weight;
}

class DSU {
 public:
  DSU() = default;
  explicit DSU(int n) : parent_(n), rank_(n, 0), count_(n) {
    for (int i = 0; i < n; ++i) {
      parent_[i] = i;
    }
  }

  int Count() {
    return count_;
  }

  int FindSet(int x) noexcept {
    if (x == parent_[x]) {
      return x;
    }
    return parent_[x] = FindSet(parent_[x]);
  }

  void Union(int x, int y) noexcept {
    x = FindSet(x);
    y = FindSet(y);
    if (x == y) {
      return;
    }
    --count_;
    if (rank_[x] < rank_[y]) {
      parent_[x] = y;
    } else {
      parent_[y] = x;
      if (rank_[x] == rank_[y]) {
        ++rank_[x];
      }
    }
  }

 private:
  std::vector<int> parent_;
  std::vector<int> rank_;
  int count_;
};

class Graph {
 public:
  std::vector<Edge> edges;
  int numVertices;

  explicit Graph(int vertices) : numVertices(vertices) {
  }

  void AddEdge(int u, int v, int weight) {
    edges.emplace_back(u, v, weight);
  }

  int KruskalMst() {
    std::sort(edges.begin(), edges.end());
    DSU dsu(numVertices);
    int mst_weight = 0;

    for (const auto& edge : edges) {
      if (dsu.FindSet(edge.v1) != dsu.FindSet(edge.v2)) {
        dsu.Union(edge.v1, edge.v2);
        mst_weight += edge.weight;
      }
    }
    return mst_weight;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int num_spies = 0;
  std::cin >> num_spies;

  Graph graph(num_spies + 1);

  for (int i = 0; i < num_spies; ++i) {
    for (int j = 0; j < num_spies; ++j) {
      int weight = 0;
      std::cin >> weight;
      if (i < j) {
        graph.AddEdge(i, j, weight);
      }
    }
  }

  for (int i = 0; i < num_spies; ++i) {
    int mission_cost = 0;
    std::cin >> mission_cost;
    graph.AddEdge(i, num_spies, mission_cost);
  }

  std::cout << graph.KruskalMst() << '\n';

  return 0;
}
