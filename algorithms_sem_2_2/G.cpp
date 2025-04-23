#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

void GetCycle(const int& vertex, const std::vector<std::vector<int>>& graph, std::vector<int>& used,
              std::vector<int>& parants, std::vector<int>& cycle) {
  used[vertex] = 1;
  for (const auto& to : graph[vertex]) {
    if (used[to] == 0) {
      parants[to] = vertex;
      GetCycle(to, graph, used, parants, cycle);
      if (!cycle.empty()) {
        return;
      }
    } else if (used[to] == 1) {
      parants[to] = vertex;
      cycle = {to};
      for (int i = parants[to]; i != to; i = parants[i]) {
        cycle.push_back(i);
      }
      std::reverse(cycle.begin(), cycle.end());
      return;
    }
  }
  used[vertex] = 2;
}

void DFS(const int& vertex, const std::vector<std::vector<int>>& graph, std::vector<bool>& used,
         std::vector<int>& answer) {
  used[vertex] = true;
  for (const auto& to : graph[vertex]) {
    if (!used[to]) {
      DFS(to, graph, used, answer);
    }
  }
  answer.push_back(vertex);
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n);
  for (int i = 0; i < m; ++i) {
    int vertex_1 = 0;
    int vertex_2 = 0;
    std::cin >> vertex_1 >> vertex_2;
    --vertex_1;
    --vertex_2;
    graph[vertex_1].push_back(vertex_2);
  }
  std::vector<int> used(n);
  std::vector<int> parants(n, -1);
  std::vector<int> cycle;
  for (int i = 0; (i < n) && cycle.empty(); ++i) {
    if (used[i] == 0) {
      GetCycle(i, graph, used, parants, cycle);
    }
  }
  if (!cycle.empty()) {
    std::cout << -1;
  } else {
    std::vector<bool> visited(n, false);
    std::vector<int> answer(n);
    for (int i = 0; i < n; ++i) {
      if (!visited[i]) {
        DFS(i, graph, visited, answer);
      }
    }
    std::reverse(answer.begin(), answer.end());
    for (int i = 0; i < n; ++i) {
      std::cout << answer[i] + 1 << ' ';
    }
  }
  return 0;
}