// 0-1 knapsack problem using branch-and-bound
#include <iostream>
#include <numeric>
#include <queue>
using namespace std;

class Solution {

public:
  unsigned int start_clock;
  unsigned int end_clock;

  const int *w, *v;
  int *k;
  int n;

  struct Node {
    bool x;
    Node *parent;
  };

  float bound(int i, int c, int cv) {
    float b = cv;
    while (i < n && w[k[i]] <= c) {
      c -= w[k[i]];
      b += v[k[i]];
      ++i;
    }
    if (i < n)
      b += 1.0 * v[k[i]] / w[k[i]] * c;
    return b;
  }

  void solve(        //
      int _n,        // number of items
      int _c,        // capacity
      const int *_w, // weights
      const int *_v, // values
      int &m,        // max value
      int *x         // solution
  ) {
    // initialize
    n = _n;
    w = _w;
    v = _v;
    k = new int[n];
    iota(k, k + n, 0);
    priority_queue<tuple<float, int, int, int, Node *>> q;
    vector<Node *> nodes;
    m = 0;
    memset(x, 0, n * sizeof(int));
    start_clock = clock();
    // solve
    sort(k, k + n, [&](int i, int j) { return v[i] * w[j] > v[j] * w[i]; });
    q.push({bound(0, _c, 0), 0, _c, 0, nullptr});
    while (1) {
      auto [b, i, c, cv, p] = q.top();
      q.pop();
      if (i == n || c == 0) {
        while (p) {
          x[k[--i]] = p->x;
          p = p->parent;
        }
        break;
      }
      if (b <= m)
        continue;
      nodes.push_back(new Node{false, p});
      q.push({bound(i + 1, c, cv), i + 1, c, cv, nodes.back()});
      if (w[k[i]] <= c) {
        m = max(m, cv + v[k[i]]);
        nodes.push_back(new Node{true, p});
        q.push({b, i + 1, c - w[k[i]], cv + v[k[i]], nodes.back()});
      }
    }
    // clean up
    end_clock = clock();
    for (auto p : nodes)
      delete p;
    delete[] k;
  }
};

extern "C" float solve(int n, int c, const int *w, const int *v, int &m,
                       int *x) {
  auto s = Solution();
  s.solve(n, c, w, v, m, x);
  return (float)(s.end_clock - s.start_clock) / CLOCKS_PER_SEC;
}