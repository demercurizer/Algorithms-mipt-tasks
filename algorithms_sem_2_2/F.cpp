#include <iostream>
#include <vector>
#include <set>

struct Vertex {
  int weight = 0;
  int vertex = 0;
  Vertex() = default;
  Vertex(int weight, int vertex) : weight(weight), vertex(vertex) {
  }
};

struct Comparator {
  bool operator()(const Vertex& lhs, const Vertex& rhs) const {
    if (lhs.weight != rhs.weight) {
      return lhs.weight < rhs.weight;
    }
    return lhs.vertex < rhs.vertex;
  }
};

int Dijkstra(std::vector<std::vector<Vertex>> graph, const int& begin, const int& end) {
  int inf = 10e8;
  std::vector<int> dist(graph.size(), inf);
  std::set<Vertex, Comparator> queue;
  queue.insert(Vertex(0, begin));
  dist[begin] = 0;
  while (!queue.empty()) {
    int vertex = queue.begin()->vertex;
    queue.erase(queue.begin());
    for (const auto& to : graph[vertex]) {
      if (dist[to.vertex] > dist[vertex] + to.weight) {
        queue.erase(Vertex(dist[vertex], to.vertex));
        dist[to.vertex] = dist[vertex] + to.weight;
        queue.insert(Vertex(dist[vertex], to.vertex));
      }
    }
  }
  if (dist[end] != inf) {
    return dist[end];
  }
  return -1;
}

int main() {
  int n = 0;
  int m = 0;
  int k = 0;
  std::cin >> n >> m;
  std::vector<std::vector<Vertex>> graph(n + 1);
  for (int i = 0; i < m; ++i) {
    int vertex_1 = 0;
    int vertex_2 = 0;
    std::cin >> vertex_1 >> vertex_2;
    graph[vertex_1].emplace_back(0, vertex_2);
    graph[vertex_2].emplace_back(1, vertex_1);
  }

  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    int vertex_1 = 0;
    int vertex_2 = 0;
    std::cin >> vertex_1 >> vertex_2;
    std::cout << Dijkstra(graph, vertex_1, vertex_2) << "\n";
  }
  return 0;
}