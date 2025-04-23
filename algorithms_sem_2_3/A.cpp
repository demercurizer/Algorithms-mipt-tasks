#include <vector>
#include <iostream>
#include <cstddef>
#include <utility>

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

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  DSU dsu(n);
  for (int i = 0; i < m; ++i) {
    int operation = 0;
    std::cin >> operation;
    if (operation == 1) {
      int first = 0;
      int second = 0;
      int w = 0;
      std::cin >> first >> second >> w;
      dsu.Union(first - 1, second - 1, w);
    } else if (operation == 2) {
      int first = 0;
      std::cin >> first;
      std::cout << dsu.Weight(first - 1) << "\n";
    }
  }
  return 0;
}
