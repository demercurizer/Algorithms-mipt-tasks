#include <iostream>
#include <vector>
#include <queue>
#include <limits>

class Graph {
 private:
  struct WeightAndVertex {
    int weight;
    int vertex;

    WeightAndVertex(int w, int v) : weight(w), vertex(v) {
    }

    bool operator<(const WeightAndVertex& other) const {
      if (weight != other.weight) {
        return weight < other.weight;
      }
      return vertex < other.vertex;
    }
  };

 public:
  explicit Graph(int size) : vertices_(size) {
  }

  void AddEdge(int u, int v, int weight) {
    vertices_[u].emplace_back(weight, v);
  }

  int Dijkstra(int start, int finish) const {
    const int k_inf = std::numeric_limits<int>::max();
    std::vector<int> distances(vertices_.size(), k_inf);
    distances[start] = 0;
    std::priority_queue<WeightAndVertex> q;
    q.emplace(0, start);
    while (!q.empty()) {
      int v = q.top().vertex;
      int distance = -q.top().weight;
      q.pop();
      if (v == finish) {
        break;
      }
      if (distance > distances[v]) {
        continue;
      }
      for (const auto& to : vertices_[v]) {
        if (distances[to.vertex] > distances[v] + to.weight) {
          distances[to.vertex] = distances[v] + to.weight;
          q.emplace(-distances[to.vertex], to.vertex);
        }
      }
    }
    return distances[finish] == k_inf ? -1 : distances[finish];
  }

 private:
  std::vector<std::vector<WeightAndVertex>> vertices_;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int vertex_amount = 0;
  int start = 0;
  int finish = 0;
  std::cin >> vertex_amount >> start >> finish;
  --start;
  --finish;

  Graph graph(vertex_amount);
  for (int i = 0; i < vertex_amount; ++i) {
    for (int j = 0; j < vertex_amount; ++j) {
      int weight = 0;
      std::cin >> weight;
      if (weight > 0) {
        graph.AddEdge(i, j, weight);
      }
    }
  }

  int shortest_distance = graph.Dijkstra(start, finish);
  std::cout << shortest_distance << '\n';

  return 0;
}
