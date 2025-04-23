#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <stack>

void PrintPath(std::vector<int>& prev, int a, int current) {
  if (current == a) {
    std::cout << a << " ";
    return;
  }
  PrintPath(prev, a, prev[current]);
  std::cout << current << " ";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int m = 0;
  int a = 0;
  int b = 0;

  std::cin >> n >> m;
  std::cin >> a >> b;

  std::vector<int> prev(n + 1);
  std::vector<std::vector<int>> graph(n + 1);
  std::vector<int> dist;
  int inf = -1;
  dist.assign(n + 1, inf);
  dist[a] = 0;
  std::queue<int> queue;
  queue.push(a);

  for (int i = 0; i < m; ++i) {
    int vertex = 0;
    int edge = 0;
    std::cin >> vertex >> edge;
    graph[vertex].emplace_back(edge);
    graph[edge].emplace_back(vertex);
  }

  while (!queue.empty()) {
    int v = queue.front();
    queue.pop();
    for (int to : graph[v]) {
      if (dist[to] != inf) {
        continue;
      }
      dist[to] = dist[v] + 1;
      prev[to] = v;
      queue.push(to);
    }
  }

  std::cout << dist[b] << "\n";
  if (dist[b] != inf) {
    PrintPath(prev, a, b);
    std::cout << "\n";
  }

  return 0;
}
