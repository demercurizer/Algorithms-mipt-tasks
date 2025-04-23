#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

struct Edge {
  int number;
  int to;
};

std::vector<std::vector<Edge>> graph(20002);
std::set<int> ans;
std::vector<bool> used(20002);
std::vector<int> ret(20002);
std::vector<int> tin(20002, 1e9);
int timer = 0;

void DFS(int vertex, int prev = -1) {
  tin[vertex] = timer++;
  ret[vertex] = tin[vertex];
  used[vertex] = true;
  for (Edge& edge : graph[vertex]) {
    if (edge.to == prev) {
      continue;
    }
    if (used[edge.to]) {
      ret[vertex] = std::min(ret[vertex], tin[edge.to]);
    } else {
      DFS(edge.to, vertex);
      ret[vertex] = std::min(ret[vertex], ret[edge.to]);
      if (ret[edge.to] > tin[vertex]) {
        ans.insert(edge.number);
      }
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int vertex_1 = 0;
    int vertex_2 = 0;
    std::cin >> vertex_1 >> vertex_2;
    graph[vertex_1].push_back({i, vertex_2});
    graph[vertex_2].push_back({i, vertex_1});
  }

  for (int i = 1; i <= n; ++i) {
    if (!used[i]) {
      DFS(i);
    }
  }
  std::cout << ans.size() << "\n";
  for (auto& to : ans) {
    std::cout << to << "\n";
  }
  return 0;
}
