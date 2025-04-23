#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
struct Vertex {
  int vertex;
  bool second;
};

std::vector<std::vector<Vertex>> graph(100002);
std::vector<int> degrees(100002, 0);
std::vector<bool> used(100002);
std::vector<int> euler_cycle;
std::vector<int> repeat_vertex(100002);
int graph_components = 0;

void DfsEulerCycle(const int& vertex) {
  for (size_t i = repeat_vertex[vertex]; i < graph[vertex].size(); ++i) {
    if (repeat_vertex[vertex] >= static_cast<int>(graph[vertex].size())) {
      break;
    }
    if (graph[vertex][i].second == 0) {
      ++graph[vertex][i].second;
      ++repeat_vertex[vertex];
      DfsEulerCycle(graph[vertex][i].vertex);
    }
  }
  euler_cycle.emplace_back(vertex);
}

void DFS(const int& vertex) {
  used[vertex] = true;
  for (const auto& to : graph[vertex]) {
    if (!used[to.vertex]) {
      DFS(to.vertex);
    }
  }
}

bool CheckCorrectEuler(const int& number_of_vertex) {
  for (int i = 1; i <= number_of_vertex; ++i) {
    if (!used[i] && graph[i].size() != 0) {  // NOLINT
      if (degrees[i] != 0) {
        return false;
      }
      DFS(i);
      ++graph_components;
    }
  }
  return (graph_components == 1);
}

void ResultCycle(const int& number_of_vertex) {
  if (!CheckCorrectEuler(number_of_vertex)) {
    std::cout << 0;
    return;
  }
  int begin_vert = 0;
  for (int i = 1; i <= number_of_vertex; ++i) {
    if (used[i]) {
      begin_vert = i;
      break;
    }
  }

  DfsEulerCycle(begin_vert);
  int size_new_path = euler_cycle.size();  // NOLINT
  std::cout << size_new_path << " ";
  for (auto to = euler_cycle.rbegin(); to != euler_cycle.rend(); ++to) {
    std::cout << *to << " ";
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    int len = 0;
    int vertex_1 = 0;
    int vertex_2 = 0;
    std::cin >> len >> vertex_1;
    for (int j = 0; j < len; ++j) {
      std::cin >> vertex_2;
      graph[vertex_1].emplace_back(vertex_2, false);
      ++degrees[vertex_1];
      --degrees[vertex_2];
      vertex_1 = vertex_2;
    }
  }
  euler_cycle.reserve(n * m);
  ResultCycle(m);
}