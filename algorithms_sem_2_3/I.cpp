#include <iostream>
#include <vector>
#include <set>

class Graph {
 public:
  struct Vertex {
    int weight;
    int vertex;
    Vertex() : weight(0), vertex(0) {
    }

    Vertex(const int& new_weight, const int& new_vertex) : weight(new_weight), vertex(new_vertex) {
    }
  };

  static bool Compare(const Vertex& v_1, const Vertex& v_2) {
    if (v_1.weight != v_2.weight) {
      return v_1.weight < v_2.weight;
    }
    return v_1.vertex < v_2.vertex;
  }

  static void Dijkstra(const std::vector<std::vector<Vertex>>& graph, const int& start) {
    const int k_inf = 2009000999;
    std::vector<int> distances(graph.size(), k_inf);
    distances[start] = 0;
    std::set<Vertex, decltype(&Compare)> q(&Compare);
    q.insert(Vertex(0, start));
    while (!q.empty()) {
      int v = q.begin()->vertex;
      q.erase(q.begin());
      for (const auto& to : graph[v]) {
        if (distances[to.vertex] > distances[v] + to.weight) {
          q.erase(Vertex(distances[to.vertex], to.vertex));
          distances[to.vertex] = distances[v] + to.weight;
          q.insert(Vertex(distances[to.vertex], to.vertex));
        }
      }
    }
    for (size_t i = 0; i < graph.size(); ++i) {
      std::cout << distances[i] << ' ';
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int k = 1;
  int vertex_amount = 0;
  int edge_amount = 0;
  int start = 0;
  std::cin >> k;
  for (int j = 0; j < k; ++j) {
    std::cin >> vertex_amount >> edge_amount;
    std::vector<std::vector<Graph::Vertex>> graph(vertex_amount);
    for (int i = 0; i < edge_amount; ++i) {
      int v_1 = 0;
      int v_2 = 0;
      int weight = 0;
      std::cin >> v_1 >> v_2 >> weight;
      graph[v_1].emplace_back(weight, v_2);
      graph[v_2].emplace_back(weight, v_1);
    }
    std::cin >> start;
    Graph::Dijkstra(graph, start);
    std::cout << '\n';
  }
  return 0;
}
