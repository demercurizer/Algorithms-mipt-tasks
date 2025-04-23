#include <vector>
#include <iostream>
#include <algorithm>
bool DFS(const int& vertex, const std::vector<std::vector<int>>& graph, std::vector<std::string>& color) {
  color[vertex] = "gray";
  for (const auto& to : graph[vertex]) {
    if (color[to] == "gray") {
      return true;
    }
    if (color[to] != "white") {
      continue;
    }
    DFS(to, graph, color);
  }
  color[vertex] = "black";
  return false;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  std::vector<std::vector<int>> graph(n + 1);
  std::vector<std::string> color(n + 1, "white");
  for (int i = 1; i < n; ++i) {
    char color_letter = ' ';
    for (int j = 0; j < n - i; ++j) {
      std::cin >> color_letter;
      if (color_letter == 'R') {
        graph[i].emplace_back(i + 1 + j);
      } else {
        graph[i + 1 + j].emplace_back(i);
      }
    }
  }
  std::string ans = "YES";
  for (int i = 1; i <= n; ++i) {
    if (DFS(i, graph, color)) {
      ans = "NO";
      break;
    }
  }
  std::cout << ans << "\n";
  return 0;
}
