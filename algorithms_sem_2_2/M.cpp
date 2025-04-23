#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

void DFS(const int& vertex, const int& prev, int& timer, const std::vector<std::vector<int>>& graph,
         std::vector<int>& tin, std::vector<int>& ret, std::vector<bool>& used, std::set<int>& queue) {
  tin[vertex] = timer++;
  ret[vertex] = tin[vertex];
  used[vertex] = true;
  int cld = 0;

  for (const auto& to : graph[vertex]) {
    if (to == prev) {
      continue;
    }
    if (used[to]) {
      ret[vertex] = std::min(ret[vertex], tin[to]);
    } else {
      cld++;
      DFS(to, vertex, timer, graph, tin, ret, used, queue);
      ret[vertex] = std::min(ret[vertex], ret[to]);
      if (prev != -1) {
        if (ret[to] >= tin[vertex]) {
          queue.insert(vertex);
        }
      } else {
        if (cld >= 2) {
          queue.insert(vertex);
        }
      }
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  int timer = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n + 1);
  std::vector<bool> used(n + 1);
  std::vector<int> tin(n + 1, 10e8);
  std::vector<int> ret(n + 1, 10e8);
  std::set<int> queue;
  for (int i = 0; i < m; ++i) {
    int vertex_1 = 0;
    int vertex_2 = 0;
    std::cin >> vertex_1 >> vertex_2;
    graph[vertex_1].emplace_back(vertex_2);
    graph[vertex_2].emplace_back(vertex_1);
  }

  for (int i = 1; i <= n; ++i) {
    if (!used[i]) {
      DFS(i, -1, timer, graph, tin, ret, used, queue);
      timer = 0;
    }
  }
  std::cout << queue.size() << "\n";
  for (const auto& to : queue) {
    std::cout << to << '\n';
  }
  return 0;
}