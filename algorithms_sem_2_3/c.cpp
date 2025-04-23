#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <limits>

const int kInf = std::numeric_limits<int>::max();

struct Edge {
  int to;
  int weight;
};

void AddEdge(std::vector<std::vector<Edge>>& graph, int u, int v, int weight) {
  graph[u].push_back({v, weight});
  graph[v].push_back({u, weight});
}

int Prim(const std::vector<std::vector<Edge>>& graph) {
  int n = static_cast<int>(graph.size());
  std::vector<int> dist(n, kInf);
  std::vector<bool> in_mst(n, false);
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> heap;

  dist[0] = 0;
  heap.emplace(0, 0);
  int total_weight = 0;

  while (!heap.empty()) {
    int v = heap.top().second;
    int weight = heap.top().first;
    heap.pop();

    if (in_mst[v]) {
      continue;
    }
    in_mst[v] = true;
    total_weight += weight;

    for (const Edge& edge : graph[v]) {
      int u = edge.to;
      int edge_weight = edge.weight;

      if (!in_mst[u] && edge_weight < dist[u]) {
        dist[u] = edge_weight;
        heap.emplace(dist[u], u);
      }
    }
  }

  return total_weight;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  std::vector<std::vector<Edge>> graph(n);

  for (int i = 0; i < m; ++i) {
    int b = 0;
    int e = 0;
    int w = 0;
    std::cin >> b >> e >> w;
    --b;
    --e;
    AddEdge(graph, b, e, w);
  }

  int total_weight = Prim(graph);
  std::cout << total_weight << std::endl;

  return 0;
}
