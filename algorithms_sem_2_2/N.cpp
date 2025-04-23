#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
  int from = 0;
  int to = 0;
  int id = 0;
};

std::vector<std::vector<Edge>> graph;
std::vector<int> tin, ret;
std::vector<bool> used;
std::vector<int> bridges;
int timer = 0;

void DFS(int v, int p = -1) {
  used[v] = true;
  tin[v] = ret[v] = timer++;
  for (const Edge& e : graph[v]) {
    if (e.id == p) { // Ребро по котрому мы пришли в verex не нуюно обрабатывать
      continue;
    }
    if (used[e.to]) {
      ret[v] = std::min(ret[v], tin[e.to]);
    } else {
      DFS(e.to, e.id);
      ret[v] = std::min(ret[v], ret[e.to]);
      if (ret[e.to] > tin[v]) {
        bridges.push_back(e.id);
      }
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  graph.resize(n);
  tin.resize(n);
  ret.resize(n);
  used.resize(n);
  for (int i = 0; i < m; ++i) {
    int vertex_1 = 0;
    int vertex_2 = 0;
    std::cin >> vertex_1 >> vertex_2;
    --vertex_1;
    --vertex_2;
    graph[vertex_1].push_back({vertex_1, vertex_2, i + 1});
    graph[vertex_2].push_back({vertex_2, vertex_1, i + 1});
  }
  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      DFS(i);
    }
  }
  std::sort(bridges.begin(), bridges.end());
  std::cout << bridges.size() << "\n";
  for (int id : bridges) {
    std::cout << id << "\n";
  }
  return 0;
}
