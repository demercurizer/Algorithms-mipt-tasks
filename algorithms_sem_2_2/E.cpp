#include <vector>
#include <iostream>
#include <set>

struct Point {
  int vertex;
  int weight;
  Point() : vertex(0), weight(0) {
  }
  Point(const int& vertex, const int& weight) : vertex(vertex), weight(weight) {
  }
};

struct Comparator {
  bool operator()(const Point& lhs, const Point& rhs) const {
    if (lhs.weight != rhs.weight) {
      return (lhs.weight < rhs.weight);
    }
    return lhs.vertex < rhs.vertex;
  }
};

int Dijkstra(const std::vector<std::vector<Point>>& graph, const int& begin, const int& end) {
  int inf = 1e9;
  std::vector<int> dist(graph.size(), inf);
  dist[begin] = 0;
  std::set<Point, Comparator> set;
  set.insert(Point(begin, 0));
  while (!set.empty()) {
    int v = set.begin()->vertex;
    set.erase(set.begin());
    for (const auto& to : graph[v]) {
      if (dist[to.vertex] > dist[v] + to.weight) {
        dist[to.vertex] = dist[v] + to.weight;
        set.erase(Point(to.vertex, dist[to.vertex]));
        set.insert(Point(to.vertex, dist[to.vertex]));
      }
    }
  }
  if (dist[end] != inf) {
    return dist[end];
  }
  return -1;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int vertex_amount = 0;
  int edge_amount = 0;
  int begin = 0;
  int end = 0;
  std::cin >> vertex_amount >> edge_amount;
  std::vector<std::vector<Point>> graph(vertex_amount);
  std::cin >> begin >> end;
  --begin;
  --end;
  for (int i = 0; i < edge_amount; ++i) {
    int v_1;
    int v_2;
    int weight;
    std::cin >> v_1 >> v_2 >> weight;
    --v_1;
    --v_2;
    graph[v_1].emplace_back(Point(v_2, weight));
  }
  std::cout << Dijkstra(graph, begin, end);
  return 0;
}