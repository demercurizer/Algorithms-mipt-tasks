#include <vector>
#include <iostream>
#include <set>

std::vector<std::vector<int>> graph(200002);
std::vector<bool> used(200002);
std::vector<int> ret(200002);
std::vector<int> tin(200002);
std::vector<int> ans(200002);
int timer = 0;

void DFS(const int& vertex, const int& prev = -1) {
  used[vertex] = true;
  tin[vertex] = timer++;
  ret[vertex] = tin[vertex];
  int children = 0;
  for (const auto& to : graph[vertex]) {
    if (to == prev) {
      continue;
    }
    if (used[to]) {
      ret[vertex] = std::min(ret[vertex], tin[to]);
    } else {
      ++children;
      DFS(to, vertex);
      ret[vertex] = std::min(ret[vertex], ret[to]);
      if (prev != -1) {
        if (ret[to] >= tin[vertex]) {
          ans[vertex] = 1;
        }
      } else {
        if (children >= 2) {
          ans[vertex] = 1;
        }
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
    int vertex_3 = 0;
    std::cin >> vertex_1 >> vertex_2 >> vertex_3;
    graph[vertex_1].emplace_back(n + i);
    graph[vertex_2].emplace_back(n + i);
    graph[vertex_3].emplace_back(n + i);
    graph[n + i].emplace_back(vertex_1);
    graph[n + i].emplace_back(vertex_2);
    graph[n + i].emplace_back(vertex_3);
  }

  for (int i = 1; i <= n + m; ++i) {
    if (!used[i]) {
      DFS(i);
    }
  }

  int count = std::count(ans.begin() + n + 1, ans.begin() + n + m + 1, 1);  // NOLINT
  std::cout << count << "\n";
  if (count > 0) {
    for (int i = n + 1; i <= n + m; ++i) {
      if (ans[i]) {
        std::cout << i - n << " ";
      }
    }
    std::cout << "\n";
  }
  return 0;
}
