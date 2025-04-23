#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int Increase(const int& number) {
  if (number / 1000 != 9) {
    return 1000 + number;
  }
  return number;
}

int Decrease(const int& number) {
  if (number % 10 != 1) {
    return number - 1;
  }
  return number;
}

int ShiftLeft(const int& number) {
  return (number % 1000) * 10 + number / 1000;
}

int ShiftRight(const int& number) {
  return (number % 10) * 1000 + number / 10;
}

void BFS(const int& begin, int& end) {
  std::vector<bool> used(10000, false);
  std::vector<int> prev(10000, -1);
  std::queue<int> q;
  used[begin] = true;
  q.push(begin);
  std::vector<int> children;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    if (v == end) {
      break;
    }
    children = {Increase(v), Decrease(v), ShiftLeft(v), ShiftRight(v)};
    for (const auto& child : children) {
      if (!used[child]) {
        used[child] = true;
        q.push(child);
        prev[child] = v;
      }
    }
  }
  std::vector<int> ans;
  while (end != -1) {
    ans.push_back(end);
    end = prev[end];
  }
  std::reverse(ans.begin(), ans.end());
  std::cout << ans.size() << '\n';
  for (const auto& a : ans) {
    std::cout << a << '\n';
  }
}

int main() {
  int begin = 0;
  int end = 0;
  std::cin >> begin >> end;
  BFS(begin, end);
  return 0;
}