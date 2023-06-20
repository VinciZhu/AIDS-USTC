// 0-1 knapsack problem using divide-and-conquer
#include <numeric>
using namespace std;

class Solution {
public:
  const int *w, *v;
  int n;
  bool **s;
  bool *visited;
  float time_limit;
  unsigned int start_clock;
  unsigned int end_clock;

  int knapsack(int i, int c) {
    float elapsed_time = (float)(clock() - start_clock) / CLOCKS_PER_SEC;
    if (elapsed_time > time_limit)
      return INT32_MIN;
    if (i == n)
      return 0;
    if (w[i] > c) {
      s[i][c] = 0;
      return knapsack(i + 1, c);
    }
    int m0, m1;
    if (rand() % 2) {
      m0 = knapsack(i + 1, c);
      m1 = v[i] + knapsack(i + 1, c - w[i]);
    } else {
      m1 = v[i] + knapsack(i + 1, c - w[i]);
      m0 = knapsack(i + 1, c);
    }
    if (!visited[i] || m0 >= 0 && m1 >= 0) {
      s[i][c] = m1 > m0;
      visited[i] = true;
      return max(m0, m1);
    }
    return INT32_MIN;
  }

  void solve(           //
      int _n,           // number of items
      int _c,           // capacity
      const int *_w,    // weights
      const int *_v,    // values
      int &_m,          // max value
      int *_x,          // solution
      float _time_limit // time limit
  ) {
    // initialize
    n = _n;
    w = _w;
    v = _v;
    s = new bool *[n];
    for (int i = 0; i < n; ++i)
      s[i] = new bool[_c + 1];
    visited = new bool[n];
    memset(visited, 0, n);
    time_limit = _time_limit;
    start_clock = clock();
    // solve
    _m = knapsack(0, _c);
    for (int i = 0, c = _c; i < n; ++i) {
      _x[i] = s[i][c];
      c -= s[i][c] * w[i];
    }
    // clean up
    end_clock = clock();
    for (int i = 0; i < n; ++i)
      delete[] s[i];
    delete[] s;
    delete[] visited;
  }
};

extern "C" float solve(int n, int c, const int *w, const int *v, int &m, int *x,
                       float time_limit) {
  auto s = Solution();
  s.solve(n, c, w, v, m, x, time_limit);
  return (float)(s.end_clock - s.start_clock) / CLOCKS_PER_SEC;
}