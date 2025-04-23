#include <iostream>
#include <vector>

void DFS(const int& vertex, std::vector<int>& top_sorted, const std::vector<std::vector<int>>& graph,
         std::vector<std::string>& color, std::vector<int>& css, const int& count) {
  color[vertex] = "gray";
  for (const int& to : graph[vertex]) {
    if (color[to] != "white") {
      continue;
    }
    DFS(to, top_sorted, graph, color, css, count);
  }
  color[vertex] = "black";
  top_sorted.push_back(vertex);
  css[vertex] = count;
}

int main() {
  int n = 0;
  int m = 0;
  int count = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n + 1);
  std::vector<std::vector<int>> graph_revert(n + 1);
  std::vector<bool> used(n + 1);
  std::vector<std::string> color(n + 1, "white");
  std::vector<int> top_sorted;
  std::vector<int> css(n + 1);
  top_sorted.reserve(2 * n);
  for (int i = 0; i < m; ++i) {
    int vertex_1 = 0;
    int vertex_2 = 0;
    std::cin >> vertex_1 >> vertex_2;
    graph[vertex_1].emplace_back(vertex_2);
    graph_revert[vertex_2].emplace_back(vertex_1);
  }

  for (int i = 1; i <= n; ++i) {
    if (color[i] == "white") {
      DFS(i, top_sorted, graph, color, css, count);
    }
  }
  std::reverse(top_sorted.begin(), top_sorted.end());
  color.assign(n + 1, "white");
  for (int i = 0; i < n; ++i) {
    if (color[top_sorted[i]] == "white") {
      ++count;
      DFS(top_sorted[i], top_sorted, graph_revert, color, css, count);
    }
  }
  std::cout << count << "\n";
  for (int i = 1; i <= n; ++i) {
    std::cout << css[i] << " ";
  }
  std::cout << "\n";
}