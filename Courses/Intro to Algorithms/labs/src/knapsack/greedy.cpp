// 0-1 knapsack problem using greedy algorithm
#include <numeric>
using namespace std;

extern "C" float solve( //
    int n,              // number of items
    int c,              // capacity
    const int *w,       // weights
    const int *v,       // values
    int &m,             // max value
    int *x              // solution
) {
  // sort items by value/weight ratio
  int *k = new int[n];
  iota(k, k + n, 0);
  unsigned int start_clock = clock();
  // solve
  sort(k, k + n, [&](int i, int j) { return v[i] * w[j] > v[j] * w[i]; });
  m = 0;
  for (int i = 0; i < n; ++i) {
    x[k[i]] = w[k[i]] <= c;
    if (x[k[i]]) {
      c -= w[k[i]];
      m += v[k[i]];
    }
  }
  // clean up
  unsigned int end_clock = clock();
  delete[] k;
  return (float)(end_clock - start_clock) / CLOCKS_PER_SEC;
}
