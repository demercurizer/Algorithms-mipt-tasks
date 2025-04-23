#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

class Graph {
 public:
  explicit Graph(int vertices) : vertices_(vertices), time_(0), bridge_count_(0) {
    adj_list_.resize(vertices_);
    visited_.resize(vertices_, false);
    entry_time_.resize(vertices_);
    low_time_.resize(vertices_);
    colors_.resize(vertices_, -1);
  }

  void AddEdge(int v1, int v2) {
    adj_list_[v1].push_back(v2);
    adj_list_[v2].push_back(v1);
  }

  void FindBridges() {
    for (int i = 0; i < vertices_; ++i) {
      if (!visited_[i]) {
        DFS(i, -1);
      }
    }
    ++bridge_count_;
  }

  void FindComponents() {
    int component_id = 0;
    for (int i = 0; i < vertices_; ++i) {
      if (colors_[i] == -1) {
        AssignColor(i, component_id++);
      }
    }
  }

  const std::set<std::pair<int, int>>& GetBridges() const {
    return bridges_;
  }

  const std::vector<int>& GetColors() const {
    return colors_;
  }

 private:
  void DFS(int v, int parent) {
    visited_[v] = true;
    entry_time_[v] = low_time_[v] = time_++;
    for (int neighbor : adj_list_[v]) {
      if (neighbor == parent) {
        continue;
      }
      if (visited_[neighbor]) {
        low_time_[v] = std::min(low_time_[v], entry_time_[neighbor]);
      } else {
        DFS(neighbor, v);
        low_time_[v] = std::min(low_time_[v], low_time_[neighbor]);
        if (low_time_[neighbor] > entry_time_[v]) {
          bridges_.emplace(std::min(v, neighbor), std::max(v, neighbor));
        }
      }
    }
  }

  void AssignColor(int v, int color) {
    colors_[v] = color;
    for (int neighbor : adj_list_[v]) {
      if (colors_[neighbor] == -1) {
        AssignColor(neighbor, color);
      }
    }
  }

  int vertices_ = 0;
  int time_ = 0;
  int bridge_count_ = 0;
  std::vector<std::vector<int>> adj_list_;
  std::vector<bool> visited_;
  std::vector<int> entry_time_;
  std::vector<int> low_time_;
  std::set<std::pair<int, int>> bridges_;
  std::vector<int> colors_;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph(n);

  std::set<std::pair<int, int>> all_edges;
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    std::cin >> u >> v;
    --u;
    --v;
    if (u != v) {
      all_edges.emplace(std::min(u, v), std::max(u, v));
      graph.AddEdge(u, v);
    }
  }

  graph.FindBridges();
  const auto& bridges = graph.GetBridges();

  for (const auto& bridge : bridges) {
    all_edges.erase(bridge);
  }

  Graph component_graph(n);
  for (const auto& edge : all_edges) {
    component_graph.AddEdge(edge.first, edge.second);
  }

  component_graph.FindComponents();
  const auto& component_colors = component_graph.GetColors();

  std::vector<std::vector<int>> component_vertices(n);
  for (int i = 0; i < n; ++i) {
    component_vertices[component_colors[i]].push_back(i);
  }

  std::vector<int> component_degrees(n, 0);
  for (auto& bridge : bridges) {
    int u = bridge.first;
    int v = bridge.second;
    for (int i = 0; i < n; ++i) {
      component_degrees[i] += std::binary_search(component_vertices[i].begin(), component_vertices[i].end(), u);
      component_degrees[i] += std::binary_search(component_vertices[i].begin(), component_vertices[i].end(), v);
    }
  }

  int result = 0;
  for (int degree : component_degrees) {
    if (degree == 1) {
      ++result;
    }
  }

  std::cout << (result + 1) / 2 << "\n";
  return 0;
}
