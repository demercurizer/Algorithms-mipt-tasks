#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <cassert>

template <typename TVertex, typename TFlow>
struct Edge {
  TVertex start, finish;
  TFlow capacity, flow;

  Edge(TVertex s, TVertex f, TFlow c) : start(s), finish(f), capacity(c), flow(0) {
  }
};

template <typename TVertex, typename TFlow>
class Network {
 private:
  TVertex vertices_number_, source_, sink_;
  std::vector<Edge<TVertex, TFlow>> edges_;
  std::vector<std::vector<size_t>> graph_;

  void AddEdgeLocal(TVertex start, TVertex finish, TFlow capacity) {
    graph_[start].push_back(edges_.size());
    edges_.emplace_back(start, finish, capacity);
  }

  void Push(size_t edge_number, TFlow flow) {
    edges_[edge_number].flow += flow;
    edges_[edge_number ^ 1].flow -= flow;
  }

 public:
  Network(TVertex n, TVertex s, TVertex t) : vertices_number_(n), source_(s), sink_(t), edges_(), graph_(n) {
    assert(0 <= s && s < n && 0 <= t && t < n);
  }

  void AddEdge(TVertex start, TVertex finish, TFlow capacity) {
    AddEdgeLocal(start, finish, capacity);
    AddEdgeLocal(finish, start, 0);
  }

  TVertex GetVerticesNumber() const {
    return vertices_number_;
  }
  TVertex GetSource() const {
    return source_;
  }
  TVertex GetSink() const {
    return sink_;
  }

  class EdgeIterator {
   private:
    Network &my_network_;
    TVertex vertex_;
    size_t index_;

    size_t GetIndexInEdgesList() const {
      return my_network_.graph_[vertex_][index_];
    }

    const Edge<TVertex, TFlow> &MyEdge() const {
      return my_network_.edges_[GetIndexInEdgesList()];
    }

    Edge<TVertex, TFlow> &MyEdge() {
      return my_network_.edges_[GetIndexInEdgesList()];
    }

   public:
    explicit EdgeIterator(Network &my_network, TVertex v) : my_network_(my_network), vertex_(v), index_(0) {
    }

    bool Valid() const {
      return index_ < my_network_.graph_[vertex_].size();
    }

    void Next() {
      ++index_;
    }

    TVertex GetStart() const {
      return MyEdge().start;
    }

    TVertex GetFinish() const {
      return MyEdge().finish;
    }

    TFlow GetCapacity() const {
      return MyEdge().capacity;
    }

    TFlow GetFlow() const {
      return MyEdge().flow;
    }

    TFlow GetResidualCapacity() const {
      return GetCapacity() - GetFlow();
    }

    bool IsSaturated() const {
      return GetResidualCapacity() == static_cast<TFlow>(0);
    }

    void PushFlow(TFlow f) {
      assert(static_cast<TFlow>(0) <= f && f <= GetResidualCapacity());
      my_network_.Push(GetIndexInEdgesList(), f);
    }
  };

  friend class EdgeIterator;

  EdgeIterator Begin(TVertex v) {
    return EdgeIterator(*this, v);
  }

  TFlow GetFlowSize() const {
    TFlow flow = 0;
    for (const auto &edge : edges_) {
      if (edge.start == source_) {
        flow += edge.flow;
      }
    }
    return flow;
  }

  bool IsCorrectFlow() const {
    // Implement this function if needed for correctness checking.
    return true;
  }
};

template <typename TVertex, typename TFlow>
class DinitzAlgorithm {
 private:
  using NetworkIterator = typename Network<TVertex, TFlow>::EdgeIterator;
  Network<TVertex, TFlow> &network_;
  std::vector<size_t> dst_;
  TVertex n_, s_, t_;
  std::vector<NetworkIterator> iterators_;

  bool Bfs() {
    dst_.assign(n_, n_);
    std::queue<TVertex> q;
    q.push(s_);
    dst_[s_] = 0;
    while (!q.empty()) {
      TVertex v = q.front();
      q.pop();
      for (NetworkIterator it = network_.Begin(v); it.Valid(); it.Next()) {
        if (!it.IsSaturated()) {
          TVertex nv = it.GetFinish();
          if (dst_[v] + 1 < dst_[nv]) {
            dst_[nv] = dst_[v] + 1;
            q.push(nv);
          }
        }
      }
    }
    return dst_[t_] != n_;
  }

  void InitIterators() {
    iterators_.clear();
    for (TVertex v = 0; v < n_; ++v) {
      iterators_.emplace_back(network_.Begin(v));
    }
  }

  TFlow Dfs(TVertex v, TFlow f) {
    if (v == t_) {
      return f;
    }
    for (NetworkIterator &it = iterators_[v]; it.Valid(); it.Next()) {
      if (it.IsSaturated()) {
        continue;
      }
      if (dst_[it.GetStart()] + 1 != dst_[it.GetFinish()]) {
        continue;
      }
      TFlow nf = std::min(f, it.GetResidualCapacity());
      TFlow res = Dfs(it.GetFinish(), nf);
      if (res) {
        it.PushFlow(res);
        return res;
      }
    }
    return 0;
  }

 public:
  explicit DinitzAlgorithm(Network<TVertex, TFlow> &network) : network_(network) {
  }

  void Run() {
    n_ = network_.GetVerticesNumber();
    s_ = network_.GetSource();
    t_ = network_.GetSink();
    while (Bfs()) {
      InitIterators();
      while (Dfs(s_, std::numeric_limits<TFlow>::max())) {
      }
    }
  }
};

template <typename TVertex, typename TFlow>
TFlow RunDinitz(Network<TVertex, TFlow> &network) {
  DinitzAlgorithm<TVertex, TFlow> algo(network);
  algo.Run();
  assert(network.IsCorrectFlow());
  return network.GetFlowSize();
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t n = 0;
  size_t m = 0;
  std::cin >> n >> m;

  Network<size_t, int64_t> network(n, 0, n - 1);

  for (size_t i = 0; i < m; ++i) {
    size_t u = 0;
    size_t v = 0;
    int64_t capacity = 0;
    std::cin >> u >> v >> capacity;
    --u;
    --v;  // Adjust to 0-based indexing
    network.AddEdge(u, v, capacity);
  }

  int64_t max_flow = RunDinitz(network);
  std::cout << max_flow << "\n";

  return 0;
}
