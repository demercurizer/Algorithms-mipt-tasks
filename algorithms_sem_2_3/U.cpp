#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

class Solve {
 public:
  using Vertex = int16_t;
  using Distance = int32_t;
  const Distance cInf = 2e9;

  Solve& Input() {
    ///////////////////////////////////////

    std::size_t vertex_count = 0;
    std::size_t edge_count = 0;
    std::size_t lecture_count = 0;

    std::cin >> vertex_count >> edge_count >> lecture_count;

    ///////////////////////////////////////

    edge_id_.resize(vertex_count + 1, std::vector<std::size_t>(vertex_count + 1));
    dp_.resize(vertex_count + 1, std::vector<Distance>(vertex_count + 1, cInf));
    next_in_path_.resize(vertex_count + 1, std::vector<Vertex>(vertex_count + 1));

    ///////////////////////////////////////

    std::vector<Vertex> vertexs(vertex_count);
    std::iota(vertexs.begin(), vertexs.end(), 1);

    ///////////////////////////////////////

    for (const auto& vertex : vertexs) {
      dp_[vertex][vertex] = 0;
    }

    ///////////////////////////////////////

    vertexs_ = std::move(vertexs);

    ///////////////////////////////////////

    Vertex from = 0;
    Vertex to = 0;
    Distance cost = 0;

    for (std::size_t i = 1; i <= edge_count; ++i) {
      std::cin >> from >> to >> cost;

      dp_[from][to] = -cost;
      edge_id_[from][to] = i;
      next_in_path_[from][to] = to;
    }

    ///////////////////////////////////////

    is_lecture_.resize(vertex_count + 1, false);
    while (lecture_count-- > 0) {
      std::cin >> from;

      is_lecture_[from] = true;
      lectures_.push_back(from);
    }

    ///////////////////////////////////////

    return *this;
  }

  Solve& Logic() {
    // DP
    for (auto intermediate : vertexs_) {
      for (auto from : vertexs_) {
        for (auto to : vertexs_) {
          if (to == intermediate || intermediate == from) {
            continue;
          }

          if (dp_[from][intermediate] == cInf || dp_[intermediate][to] == cInf) {
            continue;
          }

          if (dp_[from][intermediate] + dp_[intermediate][to] < dp_[from][to]) {
            dp_[from][to] = std::max(dp_[from][intermediate] + dp_[intermediate][to], -cInf);
            next_in_path_[from][to] = next_in_path_[from][intermediate];
          }
        }
      }
    }

    // find negative cycle
    for (auto from : vertexs_) {
      for (auto to : vertexs_) {
        for (auto intermediate : vertexs_) {
          if (!is_lecture_[from] || !is_lecture_[to]) {
            continue;
          }

          if (dp_[from][intermediate] >= cInf || dp_[intermediate][to] >= cInf) {
            continue;
          }

          if (dp_[intermediate][intermediate] < 0) {
            lol_ = true;
            return *this;
          }
        }
      }
    }

    return *this;
  }

  void OutPut() {
    if (lol_) {
      std::cout << "infinitely kind\n";
      return;
    }

    for (std::size_t i = 0; i + 1 < lectures_.size(); ++i) {
      Vertex current = lectures_[i];

      while (current != lectures_[i + 1]) {
        path_.push_back(current);

        current = next_in_path_[current][lectures_[i + 1]];
      }
    }

    path_.push_back(lectures_.back());

    std::cout << path_.size() - 1 << '\n';

    for (std::size_t i = 0; i + 1 < path_.size(); ++i) {
      std::cout << edge_id_[path_[i]][path_[i + 1]] << ' ';
    }
  }

 private:
  bool lol_{false};
  std::vector<Vertex> vertexs_;
  std::vector<std::vector<std::size_t>> edge_id_;
  std::vector<std::vector<Vertex>> next_in_path_;
  std::vector<Vertex> path_;
  std::vector<bool> is_lecture_;
  std::vector<std::vector<Distance>> dp_;
  std::vector<Vertex> lectures_;
};

int main() {
  Solve{}.Input().Logic().OutPut();
}
