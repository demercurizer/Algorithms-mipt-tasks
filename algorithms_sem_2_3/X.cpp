#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

template <typename T>
void Print(T& container);

struct VectorHasher {
  template <typename T>
  int operator()(const std::vector<T>& v) const {
    int hash = v.size();
    for (auto& i : v) {
      hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }
    return hash;
  }
};

template <typename T, typename U>
std::pair<T, U> operator+(const std::pair<T, U>& l, const std::pair<T, U>& r) {
  return {l.first + r.first, l.second + r.second};
}

template <typename T, typename U>
std::pair<T, U> operator-(const std::pair<T, U>& l, const std::pair<T, U>& r) {
  return {l.first - r.first, l.second - r.second};
}

template <typename T>
int64_t ManhattanDistance(std::pair<T, T> left, std::pair<T, T> right) {
  return std::abs(left.first - right.first) + std::abs(left.second - right.second);
}

template <typename T>
std::pair<int32_t, int32_t> GetZeroPos(T& state) {
  int32_t row = 0;
  std::pair<int32_t, int32_t> zero_pos;
  for (int32_t i = 0; i < 3 * 3; ++i) {
    if (i % 3 == 0 && i != 0) {
      ++row;
    }
    if (state[i] == 0) {
      zero_pos = {i % 3, row};
    }
  }
  return zero_pos;
}

template <typename T>
char CompareTwoStates(T& first, T& second) {
  char res = 0;
  auto first_zero = GetZeroPos(first);
  auto second_zero = GetZeroPos(second);

  auto sub = second_zero - first_zero;

  if (sub.first == 1) {
    res = 'R';
  } else if (sub.first == -1) {
    res = 'L';
  } else if (sub.second == 1) {
    res = 'D';
  } else {
    res = 'U';
  }
  return res;
}

std::vector<std::vector<int32_t>> GenerateStates(std::vector<int32_t>& state) {
  // firstly, we need to find 0 position in given state
  std::vector<std::vector<int32_t>> res;
  auto zero_pos = GetZeroPos(state);
  std::vector<std::pair<int32_t, int32_t>> transform{{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
  for (size_t i = 0; i < transform.size(); ++i) {
    transform[i] = transform[i] + zero_pos;
  }

  // now we need to verify what transformations are valid

  std::vector<bool> valid(4, true);
  for (size_t i = 0; i < transform.size(); ++i) {
    if (transform[i].first < 0 || transform[i].first > (3 - 1) || transform[i].second < 0 ||
        transform[i].second > (3 - 1)) {
      valid[i] = false;
    }
  }

  for (size_t i = 0; i < transform.size(); ++i) {
    if (!valid[i]) {
      continue;
    }
    res.emplace_back(state);
    // perform swap
    std::swap(res.back()[zero_pos.first + zero_pos.second * 3],
              res.back()[transform[i].first + transform[i].second * 3]);
  }
  return res;
}

template <typename Vertex>
void Astar(const Vertex& vertex) {
  std::vector<int32_t> termination_state;
  for (int32_t i = 1; i < 3 * 3; ++i) {
    termination_state.push_back(i);
  }
  termination_state.push_back(0);
  std::vector<std::pair<int32_t, int32_t>> positions(3 * 3);
  int32_t row = 0;
  for (int32_t i = 1; i < 3 * 3 - 1; ++i) {
    if (i % 3 == 0 && i != 0) {
      ++row;
    }
    positions[i] = {i % 3, row};
  }
  positions[0] = {3 - 1, 3 - 1};
  std::unordered_map<Vertex, uint64_t, VectorHasher> dist;
  std::unordered_map<Vertex, uint64_t, VectorHasher> heuristic;
  std::unordered_map<Vertex, Vertex, VectorHasher> parent;

  auto calculate_h = [size = 3, &positions]<typename T>(T& state) {
    if (state.empty()) {
    }
    int32_t row = 0;
    int64_t res = 0;
    for (int32_t i = 0; i < size * size; ++i) {
      if (i % size == 0 && i != 0) {
        ++row;
      }
      res += ManhattanDistance({i % size, row}, positions[i]);
    }
    return res;
  };

  auto function = [&dist, &heuristic]<typename T>(T& state) { return dist[state] + heuristic[state]; };

  dist[vertex] = 0;
  heuristic[vertex] = calculate_h(vertex);
  std::priority_queue<std::pair<int64_t, Vertex>> queue;
  queue.push({function(vertex), vertex});
  while (!queue.empty()) {
    auto cur_state = queue.top().second;
    queue.pop();

    // if (cur_d > function(cur_state)) continue;

    auto derived_states = GenerateStates(cur_state);

    for (auto& state : derived_states) {
      uint64_t found_g = dist[cur_state] + 1;
      bool update_g = true;
      if (!dist.contains(state)) {
        // we haven't visited this vertex yet
        heuristic[state] = calculate_h(state);
        queue.push({-found_g, state});
      } else {
        update_g = (found_g < dist[state]);
      }

      if (update_g) {
        dist[state] = found_g;
        parent[state] = cur_state;
      }
    }
  }
  if (!dist.contains(termination_state)) {
    std::cout << -1;
    return;
  }
  std::cout << dist[termination_state] << "\n";
  // now, we need to recover the ansewer
  auto state = termination_state;
  std::vector<char> path;
  while (state != vertex) {
    path.push_back(CompareTwoStates(parent[state], state));
    state = parent[state];
  }
  std::reverse(path.begin(), path.end());
  Print(path);
}

template <typename Cont>
void Print(Cont& container) {
  for (auto& elem : container) {
    std::cout << elem;
  }
}

int main() {
  std::vector<int32_t> starting_state;

  int32_t element = 0;
  for (int32_t i = 0; i < 9; ++i) {
    std::cin >> element;
    starting_state.push_back(element);
  }

  Astar(starting_state);
}