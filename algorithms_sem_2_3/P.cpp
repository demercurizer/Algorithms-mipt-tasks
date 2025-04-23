#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

// Класс для представления ребра графа
class Edge {
 public:
  int vertex;
  int current_flow;
  int max_flow;
  Edge(int v, int current, int max) : vertex(v), current_flow(current), max_flow(max) {
  }

  Edge() = default;
};

// Класс для представления графа и основных алгоритмов работы с ним
class FlowNetwork {
 public:
  int vertex_count;
  std::vector<std::vector<int>> adj_list;
  std::vector<Edge> edge_list;
  std::vector<int> visited;

  explicit FlowNetwork(int vertices) {
    vertex_count = vertices;
    adj_list.resize(vertex_count);
    visited.resize(vertex_count);
  }

  int PerformBFS(int target);
  bool ValidateFlow();
};

int FlowNetwork::PerformBFS(int target) {
  const int kInfinity = 1e9;
  std::vector<int> distance(vertex_count, kInfinity);
  std::vector<int> parent(vertex_count, -1);
  std::vector<int> edge_index(vertex_count, -1);
  distance[0] = 0;
  std::queue<int> bfs_queue;
  bfs_queue.push(0);

  while (!bfs_queue.empty()) {
    int current_vertex = bfs_queue.front();
    bfs_queue.pop();
    for (const auto& edge_idx : adj_list[current_vertex]) {
      if (edge_list[edge_idx].current_flow < edge_list[edge_idx].max_flow) {
        int next_vertex = edge_list[edge_idx].vertex;
        if (distance[next_vertex] > distance[current_vertex] + 1) {
          parent[next_vertex] = current_vertex;
          edge_index[next_vertex] = edge_idx;
          distance[next_vertex] = distance[current_vertex] + 1;
          bfs_queue.push(next_vertex);
        }
      }
    }
  }

  if (distance[target] == kInfinity) {
    return 0;
  }

  int min_flow = kInfinity;
  for (int v = target; v != 0; v = parent[v]) {
    min_flow = std::min(min_flow, edge_list[edge_index[v]].max_flow - edge_list[edge_index[v]].current_flow);
  }

  for (int v = target; v != 0; v = parent[v]) {
    edge_list[edge_index[v]].current_flow += min_flow;
    edge_list[edge_index[v] ^ 1].current_flow -= min_flow;
  }

  return 1;
}

bool FlowNetwork::ValidateFlow() {
  while (PerformBFS(vertex_count - 1)) {
  }

  int incoming_flow = 0, outgoing_flow = 0;

  for (int edge_idx : adj_list[0]) {
    incoming_flow += edge_list[edge_idx].current_flow;
  }

  for (int edge_idx : adj_list[vertex_count - 1]) {
    outgoing_flow += edge_list[edge_idx ^ 1].current_flow;
  }

  return incoming_flow == outgoing_flow;
}

// Класс для представления молекулярной сетки и её обработки
class MolecularGrid {
 public:
  int width, height;
  std::vector<std::string> grid;

  MolecularGrid(int w, int h) : width(w), height(h) {
    grid.resize(height);
  }

  void ReadInput();
  FlowNetwork CreateNetwork();
};

void MolecularGrid::ReadInput() {
  for (int i = 0; i < height; ++i) {
    std::cin >> grid[i];
  }
}

FlowNetwork MolecularGrid::CreateNetwork() {
  FlowNetwork network(width * height + 2);
  int edge_count = 0, valid_cells = 0;

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      char element = grid[i][j];
      int valency = 0;

      if (element == 'H')
        valency = 1;
      else if (element == 'O')
        valency = 2;
      else if (element == 'N')
        valency = 3;
      else if (element == 'C')
        valency = 4;
      else
        continue;

      ++valid_cells;

      if ((i + j) % 2 == 0) {
        network.adj_list[0].push_back(edge_count);
        network.adj_list[i * width + j + 1].push_back(edge_count + 1);
        network.edge_list.emplace_back(i * width + j + 1, 0, valency);
        network.edge_list.emplace_back(0, 0, 0);
        edge_count += 2;

        if (j > 0 && grid[i][j - 1] != '.') {
          network.adj_list[i * width + j + 1].push_back(edge_count);
          network.adj_list[i * width + j].push_back(edge_count + 1);
          network.edge_list.emplace_back(i * width + j, 0, 1);
          network.edge_list.emplace_back(i * width + j + 1, 0, 0);
          edge_count += 2;
        }

        if (j < width - 1 && grid[i][j + 1] != '.') {
          network.adj_list[i * width + j + 1].push_back(edge_count);
          network.adj_list[i * width + j + 2].push_back(edge_count + 1);
          network.edge_list.emplace_back(i * width + j + 2, 0, 1);
          network.edge_list.emplace_back(i * width + j + 1, 0, 0);
          edge_count += 2;
        }

        if (i > 0 && grid[i - 1][j] != '.') {
          network.adj_list[i * width + j + 1].push_back(edge_count);
          network.adj_list[i * width + j + 1 - width].push_back(edge_count + 1);
          network.edge_list.emplace_back(i * width + j + 1 - width, 0, 1);
          network.edge_list.emplace_back(i * width + j + 1, 0, 0);
          edge_count += 2;
        }

        if (i < height - 1 && grid[i + 1][j] != '.') {
          network.adj_list[i * width + j + 1].push_back(edge_count);
          network.adj_list[i * width + j + 1 + width].push_back(edge_count + 1);
          network.edge_list.emplace_back(i * width + j + 1 + width, 0, 1);
          network.edge_list.emplace_back(i * width + j + 1, 0, 0);
          edge_count += 2;
        }
      } else {
        network.adj_list[i * width + j + 1].push_back(edge_count);
        network.adj_list[width * height + 1].push_back(edge_count + 1);
        network.edge_list.emplace_back(width * height + 1, 0, valency);
        network.edge_list.emplace_back(i * width + j + 1, 0, 0);
        edge_count += 2;
      }
    }
  }

  return network;
}

int main() {
  int height, width;
  std::cin >> height >> width;

  MolecularGrid grid(width, height);
  grid.ReadInput();

  FlowNetwork network = grid.CreateNetwork();

  if (network.ValidateFlow()) {
    std::cout << "Valid";
  } else {
    std::cout << "Invalid";
  }
}
