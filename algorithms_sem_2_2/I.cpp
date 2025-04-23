#include <iostream>
#include <vector>

void DFS(int vertex, std::vector<std::vector<int>>& graph, std::vector<bool>& used, std::vector<int>& groop) {
  used[vertex] = true;
  groop.push_back(vertex);
  for (auto to : graph[vertex]) {
    if (!used[to]) {
      DFS(to, graph, used, groop);
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  int counter = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n + 1);
  std::vector<bool> used(n + 1);
  std::vector<std::vector<int>> groop;
  for (int i = 1; i <= m; ++i) {
    int vertex_1 = 0;
    int vertex_2 = 0;
    std::cin >> vertex_1 >> vertex_2;
    graph[vertex_1].push_back(vertex_2);
    graph[vertex_2].push_back(vertex_1);
  }

  for (int i = 1; i <= n; ++i) {
    if (!used[i]) {
      groop.push_back(std::vector<int>());
      DFS(i, graph, used, groop[counter]);
      ++counter;
    }
  }
  std::cout << counter << "\n";
  for (size_t i = 0; i < groop.size(); ++i) {
    std::cout << groop[i].size() << "\n";
    for (auto to : groop[i]) {
      std::cout << to << " ";
    }
    std::cout << "\n";
  }
  return 0;
}