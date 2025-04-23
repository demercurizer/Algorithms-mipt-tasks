#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <stack>

bool BFS(const std::vector<std::vector<int>>& graph, int n, int i) {
  std::vector<int> dist;
  std::vector<int> prev(n + 1);
  int inf = 0;
  dist.assign(n + 1, inf);
  dist[i] = 1;
  std::queue<int> queue;
  queue.push(i);
  while (!queue.empty()) {
    int v = queue.front();
    queue.pop();
    for (int to : graph[v]) {
      if (dist[to] == inf) {
        queue.push(to);
        dist[to] = -dist[v];
      }
      if (dist[v] == dist[to]) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int m = 0;

  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n + 1);

  for (int i = 0; i < m; ++i) {
    int vertex = 0;
    int edge = 0;
    std::cin >> vertex >> edge;
    graph[vertex].emplace_back(edge);
    graph[edge].emplace_back(vertex);
  }
  std::string ans = "YES";
  for (int i = 1; i <= n; ++i) {
    if (!BFS(graph, n, i)) {
      ans = "NO";
      continue;
    };
  }
  std::cout << ans << "\n";
  return 0;
}
