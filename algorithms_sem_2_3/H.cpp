#include <iostream>
#include <vector>
#include <limits>

class Edge {
 public:
  int v_1 = 0;
  int v_2 = 0;
  int weight = 0;
};

std::istream& operator>>(std::istream& element, Edge& edge) {
  element >> edge.v_1 >> edge.v_2 >> edge.weight;
  return element;
}

class Graph {
 public:
  std::vector<std::vector<Edge>> adjacency_list;

  explicit Graph(int vertex_count) : adjacency_list(vertex_count) {
  }

  void AddEdge(const Edge& edge) {
    adjacency_list[edge.v_1].push_back(edge);
  }

  int FindShortestPath(int start, int finish, int all_nights) {
    const int k_inf = std::numeric_limits<int>::max();
    std::vector<int> dist(adjacency_list.size(), k_inf);
    dist[start] = 0;

    for (int i = 0; i < std::min(all_nights, static_cast<int>(adjacency_list.size())); ++i) {
      std::vector<int> temp(dist);
      for (const auto& edge_list : adjacency_list) {
        for (const auto& edge : edge_list) {
          if (dist[edge.v_1] != k_inf && temp[edge.v_2] > dist[edge.v_1] + edge.weight) {
            temp[edge.v_2] = dist[edge.v_1] + edge.weight;
          }
        }
      }
      dist = temp;
    }

    return dist[finish] == k_inf ? -1 : dist[finish];
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int vertex_amount = 0;
  int edge_amount = 0;
  int all_nights = 0;
  int start = 0;
  int finish = 0;
  std::cin >> vertex_amount >> edge_amount >> all_nights >> start >> finish;

  Graph graph(vertex_amount + 1);
  for (int i = 0; i < edge_amount; ++i) {
    Edge edge;
    std::cin >> edge;
    graph.AddEdge(edge);
  }

  std::cout << graph.FindShortestPath(start, finish, all_nights);
  return 0;
}
