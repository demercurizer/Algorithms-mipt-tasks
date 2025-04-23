#include <iostream>
#include <vector>

void DFS(int vertex, std::vector<std::vector<int>>& graph, std::vector<bool>& used) {
  used[vertex] = true;
  for (auto to: graph[vertex]) {
    if(!used[to]) {
      DFS(to, graph, used);
    }
  }
}

int main() {
  int k = 0;
  int counter = 0;
  std::cin >> k;
  std::vector<std::vector<int>> graph(k + 1);
  std::vector<bool> used(k + 1);
  for (int i = 1; i <= k; ++i) {
    int vertex = 0;
    std::cin >> vertex;
    graph[i].push_back(vertex);
    graph[vertex].push_back(i);
  }

  for (int i = 1; i <= k; ++i) {
    if (!used[i]) {
      DFS(i, graph, used);
      ++counter;
    }
  }

  std::cout << counter << "\n";
  return 0;
}