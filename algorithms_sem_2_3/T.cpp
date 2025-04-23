#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <limits>
#include <optional>
#include <numeric>

class Solve {
 public:
  using Vertex = std::size_t;
  using Distance = std::size_t;

  struct Edge {
    Vertex to;
    Distance cost;
  };

  Solve() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
  }

  Solve& Input() {
    std::size_t vertex_count = 0;
    std::size_t edge_count = 0;
    std::size_t virus_count = 0;
    std::cin >> vertex_count >> edge_count >> virus_count;

    graph_.resize(vertex_count);
    virus_.resize(virus_count);

    for (auto& vertex : virus_) {
      std::cin >> vertex;
      --vertex;
    }

    Vertex from = 0;
    Vertex to = 0;
    Distance cost = 0;
    for (std::size_t i = 0; i < edge_count; ++i) {
      std::cin >> from >> to >> cost;
      --from;
      --to;
      graph_[from].push_back({to, cost});
      graph_[to].push_back({from, cost});
    }

    std::cin >> start_ >> target_;
    --start_;
    --target_;

    return *this;
  }

  Solve& Logic() {
    distance_to_ = Dijkstra(target_);

    std::optional<Distance> min_virus_distance;
    for (const auto& vertex : virus_) {
      if (!min_virus_distance || distance_to_[vertex] < *min_virus_distance) {
        min_virus_distance = distance_to_[vertex];
      }
    }

    if (*min_virus_distance <= distance_to_[start_]) {
      ans_ = std::nullopt;
    } else {
      ans_ = distance_to_[start_];
    }

    return *this;
  }

  void OutPut() {
    if (!ans_) {
      std::cout << -1;
    } else {
      std::cout << *ans_;
    }
  }

 private:
  std::vector<std::vector<Edge>> graph_;
  std::vector<Vertex> virus_;
  Vertex start_, target_;
  std::optional<Distance> ans_;
  std::vector<Distance> distance_to_;

  std::vector<Distance> Dijkstra(Vertex source) {
    std::vector<Distance> distance(graph_.size(), std::numeric_limits<Distance>::max());
    std::set<std::pair<Distance, Vertex>> min_heap;
    distance[source] = 0;
    min_heap.emplace(0, source);

    while (!min_heap.empty()) {
      auto [dist, from] = *min_heap.begin();
      min_heap.erase(min_heap.begin());

      for (const auto& edge : graph_[from]) {
        if (distance[edge.to] > dist + edge.cost) {
          min_heap.erase({distance[edge.to], edge.to});
          distance[edge.to] = dist + edge.cost;
          min_heap.emplace(distance[edge.to], edge.to);
        }
      }
    }

    return distance;
  }
};

int main() {
  Solve{}.Input().Logic().OutPut();
}
