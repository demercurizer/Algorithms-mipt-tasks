#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>

class Graph {
 public:
  explicit Graph(int n) : adj_(n), used_(n), vertex_amount_(n) {
  }

  void AddEdge(int v_1, int v_2) {
    adj_[v_1].push_back(v_2);
    adj_[v_2].push_back(v_1);
  }

  void DFS(int vertex, int from, bool& cycle) {
    used_[vertex] = 1;
    for (const auto& to : adj_[vertex]) {
      if (to == from) {
        continue;
      }
      if (used_[to] == 0) {
        DFS(to, vertex, cycle);
      } else if (used_[to] == 1) {
        cycle = true;
      }
    }
    used_[vertex] = 2;
  }

  bool CheckSequence(const std::string& subsequence) {
    bool cycle = false;
    DFS(0, -1, cycle);
    if (cycle || (std::find(used_.begin(), used_.end(), 0) != used_.end())) {
      return false;
    }
    for (int i = 0; i < vertex_amount_; ++i) {
      if (subsequence[i] == 'H') {
        if (adj_[i].size() != 1 || subsequence[adj_[i][0]] != 'C') {
          return false;
        }
      } else {
        if (adj_[i].size() == 4) {
          std::set<int> temp(adj_[i].begin(), adj_[i].end());
          if (temp.size() != 4) {
            return false;
          }
        } else {
          return false;
        }
      }
    }
    return true;
  }

 private:
  std::vector<std::vector<int>> adj_;
  std::vector<int> used_;
  int vertex_amount_;
};

int main() {
  int vertex_amount = 0;
  int edge_amount = 0;
  std::cin >> vertex_amount >> edge_amount;
  std::string subsequence;
  std::cin >> subsequence;
  Graph graph(vertex_amount);
  for (int i = 0; i < edge_amount; ++i) {
    int v_1 = 0;
    int v_2 = 0;
    std::cin >> v_1 >> v_2;
    if (v_1 == v_2) {
      std::cout << "NO";
      return 0;
    }
    --v_1;
    --v_2;
    graph.AddEdge(v_1, v_2);
  }
  if (graph.CheckSequence(subsequence)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}
