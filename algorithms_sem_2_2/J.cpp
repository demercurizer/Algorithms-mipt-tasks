#include <iostream>
#include <vector>

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

void DFSCycle(const std::vector<std::vector<int>>& graph, const int& vertex, std::vector<std::string>& color,
              std::vector<int>& parents, std::vector<int>& cycle) {
  color[vertex] = "gray";
  for (const auto& to : graph[vertex]) {
    if (color[to] == "white") {
      parents[to] = vertex;
      DFSCycle(graph, to, color, parents, cycle);
      if (!cycle.empty()) {
        return;
      }
    } else if (color[to] == "gray") {
      parents[to] = vertex;
      cycle = {to};
      for (int i = parents[to]; i != to; i = parents[i]) {
        cycle.push_back(i);
      }
      std::reverse(cycle.begin(), cycle.end());
      return;
    }
  }
  color[vertex] = "black";
}

void DFS(const int& vertex, std::vector<std::vector<int>> graph&, std::vector<int>& tin, std::vector<int>& tout,
         std::vector<int>& color, int& timer) {
  tin = timer++;
  color[vertex] = "gray";
  for (int to : graph[vertex]) {
    if (color[to] != "while") {
      continue;
    }
    DFS(to, grpah, tin, tout, color, timer)
  }
  tout[vertex] = timer++;
  color[vertex] = "black";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n);
  std::vector<std::string> color(n, "white");
  std::vector<int> parents(n, -1);
  std::vector<int> cycle;

  for (int i = 0; i < m; ++i) {
    int vertex_1 = 0;
    int vertex_2 = 0;
    std::cin >> vertex_1 >> vertex_2;
    --vertex_1;
    --vertex_2;
    graph[vertex_1].push_back(vertex_2);
  }
  for (int i = 0; (i < n) && cycle.empty(); ++i) {
    if (color[i] == "white") {
      DFSCycle(graph, i, color, parents, cycle);
    }
  }
  if (cycle.empty()) {
    std::cout << "NO";
  } else {
    std::cout << "YES" << '\n';
    for (const auto& c : cycle) {
      std::cout << c + 1 << ' ';
    }
  }
  return 0;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n + 1);
  std::vector<string> color(n + 1, "white");
  std::vector<int> parents(n + 1, -1);
  std::vector<int> tin(n + 1);
  std::vector<int> tout(n + 1);
  int timer = 0;
  for (int i = 0; i < m; ++i) {
    int vertex_1 = 0;
    int vertex_2 = 0;
    std::cin >> vertex_1 >> vertex_2;
    graph[vertex_1].emplace_back(vertex_2);
  }

  for (int i = 0; i < n; ++i) {
    if (color[v] == "white") {
      DFS(i, graph, tin, tout, color, timer);
    }
  }
  return 0;
}