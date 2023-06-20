// 0-1 knapsack problem using dynamic programming
#include <numeric>
using namespace std;

extern "C" float solve( //
    int n,              // number of items
    int c,              // capacity
    const int *w,       // weights
    const int *v,       // values
    int &_m,            // max value
    int *x              // solution
) {
  // initialize
  bool **s = new bool *[n];
  for (int i = 0; i < n; ++i)
    s[i] = new bool[c + 1];
  int **m = new int *[n + 1];
  for (int i = 0; i <= n; ++i)
    m[i] = new int[c + 1];
  unsigned int start_clock = clock();
  // solve
  for (int j = 0; j <= c; ++j) {
    m[n][j] = 0;
  }
  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j < w[i]; ++j) {
      s[i][j] = 0;
      m[i][j] = m[i + 1][j];
    }
    for (int j = w[i]; j <= c; ++j) {
      int m0 = m[i + 1][j];
      int m1 = v[i] + m[i + 1][j - w[i]];
      s[i][j] = m1 > m0;
      m[i][j] = s[i][j] ? m1 : m0;
    }
  }
  _m = m[0][c];
  for (int i = 0, j = c; i < n; ++i) {
    x[i] = s[i][j];
    j -= s[i][j] ? w[i] : 0;
  }
  // clean up
  unsigned int end_clock = clock();
  for (int i = 0; i < n; ++i)
    delete[] s[i];
  delete[] s;
  for (int i = 0; i <= n; ++i)
    delete[] m[i];
  delete[] m;
  return (float)(end_clock - start_clock) / CLOCKS_PER_SEC;
}
