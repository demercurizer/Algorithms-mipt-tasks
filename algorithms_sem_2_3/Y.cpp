#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <numeric>
#include <cmath>
#include <cstdint>
#include <string>
#include <algorithm>
// NOLINTBEGIN
template <int8_t N>
struct Field {
  Field(const std::vector<int8_t>& field) : field_(field) {
    for (int8_t i = 0; i < N * N; ++i) {
      if (field_[i] == 0) {
        pos_x_zero = i % N;
        pos_y_zero = i / N;
      }
    }
  }
  Field() = default;

  int64_t CalculateEvristic() const {
    int64_t ans = 0;

    ans += ManhattanEvristic();
    ans += LinearConflictEvristic();
    ans += CornerEvristic();
    ans += LastMoveEvristic();

    return ans;
  }

  bool CanRight() {
    return pos_x_zero < N - 1;
  }
  bool CanLeft() {
    return pos_x_zero > 0;
  }
  bool CanDown() {
    return pos_y_zero < N - 1;
  }
  bool CanUp() {
    return pos_y_zero > 0;
  }

  std::vector<int8_t> GetRight() {
    auto new_field = field_;
    std::swap(new_field[N * pos_y_zero + pos_x_zero], new_field[N * pos_y_zero + pos_x_zero + 1]);
    return new_field;
  }
  std::vector<int8_t> GetLeft() {
    auto new_field = field_;
    std::swap(new_field[N * pos_y_zero + pos_x_zero], new_field[N * pos_y_zero + pos_x_zero - 1]);
    return new_field;
  }
  std::vector<int8_t> GetDown() {
    auto new_field = field_;
    std::swap(new_field[N * pos_y_zero + pos_x_zero], new_field[N * (pos_y_zero + 1) + pos_x_zero]);
    return new_field;
  }
  std::vector<int8_t> GetUp() {
    auto new_field = field_;
    std::swap(new_field[N * pos_y_zero + pos_x_zero], new_field[N * (pos_y_zero - 1) + pos_x_zero]);
    return new_field;
  }

  bool operator==(const Field<N>& other) const {
    return field_ == other.field_;
  }

  char WhatDirection(const Field<N>& parent) const {
    int64_t dx = pos_x_zero - parent.pos_x_zero;
    int64_t dy = pos_y_zero - parent.pos_y_zero;

    if (dx == -1) {
      return 'L';
    }

    if (dx == 1) {
      return 'R';
    }

    if (dy == -1) {
      return 'U';
    }

    if (dy == 1) {
      return 'D';
    }

    return '0';
  }

  bool IsSolvable() {
    int8_t inversions = 0;

    for (int8_t i = 0; i < N * N; ++i) {
      if (field_[i] == 0) {
        continue;
      }
      for (int8_t j = 0; j < i; ++j) {
        if (field_[j] > field_[i]) {
          ++inversions;
        }
      }
    }

    if (N % 2 == 0) {
      inversions += pos_y_zero;
    }

    return (inversions + N) % 2 != 0;
  }

 private:
  int64_t ManhattanEvristic() const {
    int64_t ans = 0;

    for (int8_t i = 0; i < N * N; ++i) {
      int8_t num = field_[i];

      if (num == 0) {
        continue;
      }

      int8_t need_x = (num - 1) % N;
      int8_t need_y = (num - 1) / N;

      ans += std::abs(need_x - (i % N)) + std::abs(need_y - (i / N));
    }
    return ans;
  }
  int64_t LinearConflictEvristic() const {
    int64_t ans = 0;

    for (int8_t y = 0; y < N; ++y) {
      for (int8_t x1 = 0; x1 < N; ++x1) {
        for (int8_t x2 = x1 + 1; x2 < N; ++x2) {
          ans += (IsConflict(y, x1, x2) ? 2 : 0);
        }
      }
    }

    return ans;
  }
  int64_t CornerEvristic() const {
    int64_t ans = 0;

    if (!ItsPosition(0, 0)) {
      if (!(InConflict(0, 1) || InConflict(1, 0))) {
        if (ItsPosition(0, 1) || ItsPosition(1, 0)) {
          ans += 2;
        }
      }
    }

    if (!ItsPosition(0, N - 1)) {
      if (!(InConflict(0, N - 2) || InConflict(1, N - 1))) {
        if (ItsPosition(0, N - 2) || ItsPosition(1, N - 1)) {
          ans += 2;
        }
      }
    }

    if (!ItsPosition(N - 1, 0)) {
      if (!(InConflict(N - 1, 1) || InConflict(N - 2, 0))) {
        if (ItsPosition(N - 1, 1) || ItsPosition(N - 2, 0)) {
          ans += 2;
        }
      }
    }

    return ans;
  }
  int64_t LastMoveEvristic() const {
    int64_t ans = 0;

    int8_t num1 = (N - 1) * N;
    int8_t num2 = N * N - 1;

    bool flag1 = false;
    bool flag2 = false;

    for (int8_t y = 0; y < N; ++y) {
      if (field_[N * y + N - 1] == num2) {
        flag1 = true;
      }
    }

    for (int8_t x = 0; x < N; ++x) {
      if (field_[N * (N - 1) + x] == num1) {
        flag2 = true;
      }
    }

    if (!flag1 && !flag2) {
      ans += 2;
    }

    return ans;
  }

  bool IsConflict(int8_t y, int8_t x1, int8_t x2) const {
    int8_t num1 = field_[N * y + x1];
    int8_t num2 = field_[N * y + x2];

    if (!num1 || !num2)
      return false;

    int8_t need_x1 = (num1 - 1) % N;
    int8_t need_y1 = (num1 - 1) / N;
    ;
    int8_t need_x2 = (num2 - 1) % N;
    int8_t need_y2 = (num2 - 1) / N;

    if ((need_y1 != y) || (need_y2 != y)) {
      return false;
    }

    if (x2 > x1) {
      return need_x1 > need_x2;
    }

    return need_x1 < need_x2;
  }
  bool InConflict(int8_t x, int8_t y) const {
    bool ans = false;
    for (int8_t x2 = 0; x2 < N; ++x2) {
      if (x2 == x) {
        continue;
      }

      if (IsConflict(y, x, x2)) {
        ans = true;
        break;
      }
    }

    return ans;
  }
  bool ItsPosition(int8_t x, int8_t y) const {
    int8_t num = field_[N * y + x];

    if (num == 0) {
      return (x == N - 1) && (y == N - 1);
    }

    return ((num - 1) % N == x) && ((num - 1) / N == y);
  }

  std::vector<int8_t> field_;
  int8_t pos_x_zero = -1;
  int8_t pos_y_zero = -1;
};

template <size_t N>
Field<N> to_field(uint64_t number) {
  std::vector<int8_t> ans;
  while (number != 0) {
    ans.push_back(number % (N * N));
    number /= N * N;
  }
  if (ans.size() != N * N) {
    ans.push_back(0);
  }
  std::reverse(ans.begin(), ans.end());
  return Field<N>(ans);
}

template <size_t N>
uint64_t to_number(const std::vector<int8_t> vector, const std::vector<std::size_t>& degrees) {
  uint64_t ans = 0;

  for (size_t i = 0; i < vector.size(); ++i) {
    ans += static_cast<std::size_t>(vector[i]) * degrees[i];
  }

  return ans;
}

int main() {
  const uint64_t N = 4;
  const uint64_t target = (N == 4 ? 1311768467463790320 : 54480996);  // for N = 3 target = 54480996

  std::vector<std::size_t> degrees;
  for (uint64_t i = 0; i < N * N; ++i) {
    degrees.push_back(std::pow(N * N, N * N - 1 - i));
  }

  std::vector<int8_t> start_field(N * N);
  for (auto& elem : start_field) {
    int16_t temp;
    std::cin >> temp;
    elem = temp;
  }

  std::unordered_map<uint64_t, std::size_t> what_index;
  what_index[to_number<N>(start_field, degrees)] = 0;

  // std::vector<uint64_t> fields_codes;
  // fields_codes.push_back(to_number<N>(start_field, degrees));

  if (!to_field<N>(to_number<N>(start_field, degrees)).IsSolvable()) {
    std::cout << -1 << '\n';
    return 0;
  }

  std::vector<int64_t> distances;
  distances.push_back(0);

  std::vector<int64_t> evristics;
  evristics.push_back(to_field<N>(to_number<N>(start_field, degrees)).CalculateEvristic());

  auto comparator = [&distances, &what_index, &evristics](uint64_t first_code, uint64_t second_code) {
    size_t first_index = what_index[first_code];
    size_t second_index = what_index[second_code];

    if (evristics[first_index] + distances[first_index] == evristics[second_index] + distances[second_index]) {
      return first_index < second_index;
    }
    return evristics[first_index] + distances[first_index] < evristics[second_index] + distances[second_index];
  };

  std::set<uint64_t, decltype(comparator)> st(comparator);
  st.insert(to_number<N>(start_field, degrees));

  std::vector<uint64_t> where_you_come;
  where_you_come.push_back(-1);

  std::vector<bool> is_finished;
  is_finished.push_back(true);

  auto AddField = [&what_index, &distances, &where_you_come, &st, &is_finished, &evristics](
                      uint64_t field_code, int64_t parent_index, uint64_t parent_code) {
    if (what_index.find(field_code) != what_index.end()) {
      std::size_t index = what_index[field_code];

      if (is_finished[index]) {
        return;
      }

      if (distances[index] > distances[parent_index] + 1) {
        st.erase(field_code);
        distances[index] = distances[parent_index] + 1;
        where_you_come[index] = parent_code;
        st.insert(field_code);
      }
    } else {
      what_index[field_code] = distances.size();
      distances.push_back(distances[parent_index] + 1);
      where_you_come.push_back(parent_code);
      is_finished.push_back(false);
      evristics.push_back(to_field<N>(field_code).CalculateEvristic());

      st.insert(field_code);
    }
  };

  while (true) {
    uint64_t cur_code = *st.begin();

    if (cur_code == target) {
      break;
    }

    size_t cur_index = what_index[cur_code];

    st.erase(st.begin());
    is_finished[cur_index] = true;

    Field<N> field = to_field<N>(cur_code);

    if (field.CanDown()) {
      AddField(to_number<N>(field.GetDown(), degrees), cur_index, cur_code);
    }

    if (field.CanUp()) {
      AddField(to_number<N>(field.GetUp(), degrees), cur_index, cur_code);
    }

    if (field.CanRight()) {
      AddField(to_number<N>(field.GetRight(), degrees), cur_index, cur_code);
    }

    if (field.CanLeft()) {
      AddField(to_number<N>(field.GetLeft(), degrees), cur_index, cur_code);
    }
  }

  std::cout << distances[what_index[*st.begin()]] << '\n';
  std::string directions;

  int64_t cur_code = *st.begin();
  int64_t prev_code = where_you_come[what_index[cur_code]];

  while (prev_code != -1) {
    directions += to_field<N>(cur_code).WhatDirection(to_field<N>(prev_code));

    cur_code = prev_code;
    prev_code = where_you_come[what_index[cur_code]];
  }
  std::reverse(directions.begin(), directions.end());

  if (N == 4) {
    for (auto& c : directions) {
      if (c == 'D') {
        c = 'U';
      } else if (c == 'U') {
        c = 'D';
      } else if (c == 'R') {
        c = 'L';
      } else if (c == 'L') {
        c = 'R';
      }
    }
  }

  std::cout << directions << '\n';
}
// NOLINTEND