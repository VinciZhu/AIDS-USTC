// 0-1 knapsack problem using monte carlo method (simulated annealing)
#include <numeric>
using namespace std;

extern "C" float solve( //
    int n,             // number of items
    int c,             // capacity
    const int *w,      // weights
    const int *v,      // values
    int &m,            // max value
    int *x,            // solution
    float max_T,       // max temperature
    float min_T,       // min temperature
    float time_limit,  // time limit
    unsigned int seed  // random seed
) {
  // initialize
  srand(seed);
  m = 0;
  int cv = 0, cw = 0;
  int *cx = new int[n];
  memset(cx, 0, sizeof(int) * n);
  float T = max_T;
  unsigned int start_clock = clock();
  // solve
  while (T > min_T) {
    int i = rand() % n;
    if (cx[i] == 0 && cw + w[i] > c)
      continue;
    int dE = (2 * cx[i] - 1) * v[i];
    if (dE < 0 || exp(-dE / T) > rand() / RAND_MAX) {
      cx[i] = 1 - cx[i];
      cw += (2 * cx[i] - 1) * w[i];
      cv += -dE;
      if (cv > m) {
        m = cv;
        copy(cx, cx + n, x);
      }
    }
    float elapsed_time = 1.0 * (clock() - start_clock) / CLOCKS_PER_SEC;
    T = max_T - elapsed_time / time_limit * (max_T - min_T);
  }
  // clean up
  unsigned int end_clock = clock();
  delete[] cx;
  return (float)(end_clock - start_clock) / CLOCKS_PER_SEC;
}