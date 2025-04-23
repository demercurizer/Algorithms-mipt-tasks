#include <vector>
#include <iostream>
#include <algorithm>

struct Graph {
 public:
  Graph(int vertices, int edges) : n_(vertices), m_(edges), timer_(0) {
    graph_.resize(n_ + m_ + 1);
    used_.resize(n_ + m_ + 1, false);
    ret_.resize(n_ + m_ + 1);
    tin_.resize(n_ + m_ + 1);
    ans_.resize(n_ + m_ + 1, 0);
  }

  void AddEdge(int vertex1, int vertex2, int vertex3) {
    graph_[vertex1].emplace_back(n_ + current_edge_);
    graph_[vertex2].emplace_back(n_ + current_edge_);
    graph_[vertex3].emplace_back(n_ + current_edge_);
    graph_[n_ + current_edge_].emplace_back(vertex1);
    graph_[n_ + current_edge_].emplace_back(vertex2);
    graph_[n_ + current_edge_].emplace_back(vertex3);
    ++current_edge_;
  }

  void FindArticulationPoints() {
    for (int i = 1; i <= n_ + m_; ++i) {
      if (!used_[i]) {
        DFS(i);
      }
    }
  }

  void PrintResults() const {
    auto count = static_cast<int>(std::count(ans_.begin() + n_ + 1, ans_.begin() + n_ + m_ + 1, 1));
    std::cout << count << "\n";
    if (count > 0) {
      for (int i = n_ + 1; i <= n_ + m_; ++i) {
        if (ans_[i]) {
          std::cout << i - n_ << " ";
        }
      }
      std::cout << "\n";
    }
  }

 private:
  void DFS(int vertex, int prev = -1) {
    used_[vertex] = true;
    tin_[vertex] = timer_++;
    ret_[vertex] = tin_[vertex];
    int children = 0;

    for (const auto& to : graph_[vertex]) {
      if (to == prev) {
        continue;
      }
      if (used_[to]) {
        ret_[vertex] = std::min(ret_[vertex], tin_[to]);
      } else {
        ++children;
        DFS(to, vertex);
        ret_[vertex] = std::min(ret_[vertex], ret_[to]);
        if (prev != -1 && ret_[to] >= tin_[vertex]) {
          ans_[vertex] = 1;
        }
        if (prev == -1 && children >= 2) {
          ans_[vertex] = 1;
        }
      }
    }
  }

  int n_ = 0;
  int m_ = 0;
  int timer_ = 0;
  int current_edge_ = 1;
  std::vector<std::vector<int>> graph_;
  std::vector<bool> used_;
  std::vector<int> ret_;
  std::vector<int> tin_;
  std::vector<int> ans_;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph(n, m);

  for (int i = 1; i <= m; ++i) {
    int vertex1 = 0;
    int vertex2 = 0;
    int vertex3 = 0;
    std::cin >> vertex1 >> vertex2 >> vertex3;
    graph.AddEdge(vertex1, vertex2, vertex3);
  }

  graph.FindArticulationPoints();
  graph.PrintResults();

  return 0;
}
