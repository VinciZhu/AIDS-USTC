// 0-1 knapsack problem using backtracking
#include <numeric>
using namespace std;

class Solution {
public:
  const int *w, *v;
  int n, c, i, m, cv;
  int *r;
  bool *x, *cx;
  int *k;
  float time_limit;
  unsigned int start_clock;
  unsigned int end_clock;

  void brance_left() {
    c -= w[i];
    cv += v[i];
    cx[i] = true;
    m = max(m, cv);
    ++i;
    knapsack();
    --i;
    c += w[i];
    cv -= v[i];
    cx[i] = false;
  }

  void brance_right() {
    ++i;
    knapsack();
    --i;
  }

  void knapsack() {
    float elapsed_time = (float)(clock() - start_clock) / CLOCKS_PER_SEC;
    if (elapsed_time > time_limit) {
      if (cv == m)
        copy(cx, cx + n, x);
      return;
    }
    if (i == n && cv == m)
      copy(cx, cx + n, x);
    if (cv + r[i] <= m)
      return;
    if (w[i] > c) {
      brance_right();
      return;
    }
    if (rand() % 2) {
      brance_left();
      brance_right();
    } else {
      brance_right();
      brance_left();
    }
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
    c = _c;
    w = _w;
    v = _v;
    r = new int[n + 1];
    r[n] = 0;
    for (int j = n - 1; j >= 0; --j)
      r[j] = v[j] + r[j + 1];
    m = cv = 0;
    x = new bool[n];
    cx = new bool[n];
    time_limit = _time_limit;
    start_clock = clock();
    // solve
    i = 0;
    knapsack();
    _m = m;
    for (int j = 0; j < n; ++j)
      _x[j] = x[j];
    // clean up
    end_clock = clock();
    delete[] r;
    delete[] x;
    delete[] cx;
  }
};

extern "C" float solve(int n, int c, const int *w, const int *v, int &m, int *x,
                       float time_limit) {
  auto s = Solution();
  s.solve(n, c, w, v, m, x, time_limit);
  return (float)(s.end_clock - s.start_clock) / CLOCKS_PER_SEC;
}