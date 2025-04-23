#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

struct Edge {
  int to;
  int cost;
};

void AddEdge(std::unordered_map<int, std::vector<Edge>>& graph, int from, int to, int cost) {
  graph[from].push_back({to, cost});
}

std::vector<int> Dijkstra(const std::unordered_map<int, std::vector<Edge>>& graph, int start, int max_vertex) {
  std::vector<int> dist(max_vertex + 1, std::numeric_limits<int>::max());
  dist[start] = 0;
  using Pii = std::pair<int, int>;
  std::priority_queue<Pii, std::vector<Pii>, std::greater<Pii>> pq;
  pq.emplace(0, start);

  while (!pq.empty()) {
    auto [currentDist, u] = pq.top();
    pq.pop();

    if (currentDist > dist[u]) {
      continue;
    }
    for (const auto& edge : graph.at(u)) {
      int v = edge.to;
      int weight = edge.cost;
      if (dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pq.emplace(dist[v], v);
      }
    }
  }
  return dist;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  int u = 0;
  int d = 0;
  int ii = 0;
  int j = 0;
  int l = 0;
  std::cin >> n >> u >> d >> ii >> j >> l;

  std::unordered_map<int, std::vector<Edge>> graph;

  for (int i = 1; i < n; ++i) {
    AddEdge(graph, i, i + 1, u);
    AddEdge(graph, i + 1, i, d);
  }

  int teleport_base = n + 1;

  for (int i = 0; i < l; ++i) {
    int k = 0;
    std::cin >> k;
    std::vector<int> stops(k);
    for (int j = 0; j < k; ++j) {
      std::cin >> stops[j];
    }
    for (int j = 0; j < k; ++j) {
      AddEdge(graph, stops[j], teleport_base + i, ii);
      AddEdge(graph, teleport_base + i, stops[j], j);
    }
  }

  std::vector<int> dist = Dijkstra(graph, 1, teleport_base + l);

  std::cout << dist[n] << '\n';

  return 0;
}
