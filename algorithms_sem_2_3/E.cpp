#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

class DSU {
 public:
  DSU() = default;
  explicit DSU(size_t n) : parent_(n), rank_(n, 0), count_(n) {
    for (size_t i = 0; i < n; ++i) {
      parent_[i] = i;
    }
  }

  size_t Count() const {
    return count_;
  }

  size_t FindSet(size_t x) noexcept {
    if (x == parent_[x]) {
      return x;
    }
    return parent_[x] = FindSet(parent_[x]);
  }

  void Union(size_t x, size_t y) noexcept {
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
  std::vector<size_t> parent_;
  std::vector<size_t> rank_;
  size_t count_;
};

class Graph {
 public:
  Graph() = default;
  explicit Graph(size_t size) {
    vertices_.resize(size + 1);
  }
  void Resize(size_t size) {
    vertices_.resize(size);
  }
  void SpecialAdd(size_t u, size_t v, size_t weight) {
    edges_.emplace(weight, std::make_pair(u, v));
  }
  size_t Size() const {
    return vertices_.size();
  }
  size_t Kruskal() {
    DSU dsu(vertices_.size());
    size_t min_weight = 0;
    while (!edges_.empty()) {
      auto edge = edges_.top();
      edges_.pop();
      size_t weight = edge.first;
      size_t u = edge.second.first;
      size_t v = edge.second.second;
      if (dsu.FindSet(u) != dsu.FindSet(v)) {
        dsu.Union(v, u);
        min_weight += weight;
      }
    }
    return min_weight;
  }

 private:
  struct Comparator {
    bool operator()(const std::pair<size_t, std::pair<size_t, size_t>>& a,
                    const std::pair<size_t, std::pair<size_t, size_t>>& b) const {
      return a.first > b.first;
    }
  };

  std::vector<std::vector<std::pair<size_t, size_t>>> vertices_;
  std::priority_queue<std::pair<size_t, std::pair<size_t, size_t>>,
                      std::vector<std::pair<size_t, std::pair<size_t, size_t>>>, Comparator>
      edges_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t n = 0;
  size_t m = 0;
  std::cin >> n >> m;
  Graph graph(n);

  for (size_t i = 0; i < m; ++i) {
    size_t v = 0;
    size_t u = 0;
    size_t w = 0;
    std::cin >> v >> u >> w;
    graph.SpecialAdd(v, u, w);
  }

  size_t ans = graph.Kruskal();
  std::cout << ans << '\n';

  return 0;
}
