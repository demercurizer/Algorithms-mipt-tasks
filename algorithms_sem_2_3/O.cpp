#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
struct Edge {
  Edge() = default;
  Edge(int from, int to, int capacity) : from(from), to(to), capacity(capacity), flow(0) {
  }

  int from = 0;
  int to = 0;
  int capacity = 0;
  int flow = 0;
};

class FlowGraph {
 public:
  explicit FlowGraph(int vertex_count) {
    adjacency_list_.resize(vertex_count + 1);
  }

  void AddEdge(int from, int to, int capacity) {
    edges_.emplace_back(from, to, capacity);
    edges_.emplace_back(to, from, 0);
    adjacency_list_[from].push_back(static_cast<int>(edges_.size()) - 2);
    adjacency_list_[to].push_back(static_cast<int>(edges_.size()) - 1);
  }

  size_t Size() const {
    return adjacency_list_.size();
  }

  const std::vector<int>& GetAdjacencyList(int vertex) const {
    return adjacency_list_[vertex];
  }

  Edge& GetEdge(int index) {
    return edges_[index];
  }

  const Edge& GetEdge(int index) const {
    return edges_[index];
  }

 private:
  std::vector<std::vector<int>> adjacency_list_;
  std::vector<Edge> edges_;
};

bool Bfs(const FlowGraph& graph, int source, int sink, std::vector<int>& parent) {
  std::fill(parent.begin(), parent.end(), -1);
  std::queue<int> q;
  q.push(source);
  parent[source] = -2;

  while (!q.empty()) {
    int current = q.front();
    q.pop();

    for (int edge_index : graph.GetAdjacencyList(current)) {
      const Edge& edge = graph.GetEdge(edge_index);

      if (parent[edge.to] == -1 && edge.capacity > edge.flow) {
        parent[edge.to] = edge_index;
        if (edge.to == sink) {
          return true;
        }
        q.push(edge.to);
      }
    }
  }

  return false;
}

int EdmondsKarp(FlowGraph& graph, int source, int sink) {
  int max_flow = 0;
  std::vector<int> parent(graph.Size());

  while (Bfs(graph, source, sink, parent)) {
    int flow = std::numeric_limits<int>::max();
    for (int v = sink; v != source;) {
      int edge_index = parent[v];
      const Edge& edge = graph.GetEdge(edge_index);
      flow = std::min(flow, edge.capacity - edge.flow);
      v = edge.from;
    }

    for (int v = sink; v != source;) {
      int edge_index = parent[v];
      Edge& edge = graph.GetEdge(edge_index);
      edge.flow += flow;
      graph.GetEdge(edge_index ^ 1).flow -= flow;
      v = edge.from;
    }

    max_flow += flow;
  }

  return max_flow;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  FlowGraph graph(n);

  for (int i = 0; i < m; ++i) {
    int from = 0;
    int to = 0;
    int capacity = 0;
    std::cin >> from >> to >> capacity;
    graph.AddEdge(from, to, capacity);
  }

  std::cout << EdmondsKarp(graph, 1, n) << '\n';
  return 0;
}
