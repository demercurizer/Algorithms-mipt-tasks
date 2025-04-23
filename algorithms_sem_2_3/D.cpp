#include <vector>
#include <iostream>
#include <cstddef>
#include <utility>
#include <algorithm>

class DSU {
 public:
  DSU() = default;
  explicit DSU(int n) : parent_(n), rank_(n, 0), weights_(n, 0), count_(n) {
    for (int i = 0; i < n; ++i) {
      parent_[i] = i;
    }
  }

  int Count() {
    return count_;
  }

  void MakeSet() {
    parent_.emplace_back(parent_.size());
    rank_.emplace_back(0ul);
    weights_.emplace_back(0);
    ++count_;
  }

  int FindSet(int x) noexcept {
    if (x == parent_[x]) {
      return x;
    }
    return parent_[x] = FindSet(parent_[x]);
  }

  void Union(int x, int y, int w) noexcept {
    x = FindSet(x);
    y = FindSet(y);
    if (x == y) {
      weights_[x] += w;
      return;
    }
    --count_;
    if (rank_[x] < rank_[y]) {
      parent_[x] = y;
      weights_[y] += weights_[x] + w;
    } else {
      parent_[y] = x;
      weights_[x] += weights_[y] + w;
      if (rank_[x] == rank_[y]) {
        ++rank_[x];
      }
    }
  }

  int Weight(int x) noexcept {
    return weights_[FindSet(x)];
  }

 private:
  std::vector<int> parent_{};
  std::vector<int> rank_{};
  std::vector<int> weights_{};
  int count_ = 0;
};

struct Edge {
  int u = 0;
  int v = 0;
  int w = 0;
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  DSU dsu(n);
  std::vector<Edge> edges(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
    --edges[i].u;
    --edges[i].v;
  }
  std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
  int total_weight = 0;
  for (const auto& edge : edges) {
    if (dsu.FindSet(edge.u) != dsu.FindSet(edge.v)) {
      dsu.Union(edge.u, edge.v, edge.w);
      total_weight += edge.w;
    }
  }
  std::cout << total_weight << "\n";
  return 0;
}
