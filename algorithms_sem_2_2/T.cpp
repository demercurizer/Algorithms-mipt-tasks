#include <iostream>
#include <vector>

class Graph {
 public:
  Graph(int vertices) : adj(vertices), subtree_size(vertices, 0), result(vertices, 0), total_vertices(vertices) {
  }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void calculatePairs() {
    dfs(0, -1);
    calculateResult(0, -1);
  }

  void printResults() const {
    for (int res : result) {
      // We divide by 2 because each pair (u, v) is counted twice
      std::cout << res / 2 << "\n";
    }
  }

 private:
  void dfs(int v, int parent) {
    subtree_size[v] = 1;
    for (int neighbor : adj[v]) {
      if (neighbor == parent)
        continue;
      dfs(neighbor, v);
      subtree_size[v] += subtree_size[neighbor];
    }
  }

  void calculateResult(int v, int parent) {
    for (int neighbor : adj[v]) {
      if (neighbor == parent)
        continue;
      result[v] += subtree_size[neighbor] * (total_vertices - subtree_size[neighbor]);
      calculateResult(neighbor, v);
    }
  }

  std::vector<std::vector<int>> adj;
  std::vector<int> subtree_size;
  std::vector<int> result;
  int total_vertices;
};

int main() {
  int V, E;
  std::cin >> V >> E;

  Graph graph(V);

  for (int i = 0; i < E; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u;  // switch to 0-based index
    --v;
    graph.addEdge(u, v);
  }

  graph.calculatePairs();
  graph.printResults();

  return 0;
}
