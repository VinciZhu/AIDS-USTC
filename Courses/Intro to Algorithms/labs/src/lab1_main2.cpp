#include "sort.hpp"
#include "utils.hpp"

const uint RAND_SEED = 42;
const int REPEAT = 5;
const size_t N = 100000;
// const size_t N = 1000;

const vector<string> SORT_NAMES{
    "sort",       "qsort",      "Insertion sort",
    "Merge sort", "Quick sort", "Randomized quick sort",
    "Heap sort",  "Radix sort", "Bucket sort"};
const vector<sort_func_t> SORT_FUNCS{
    [](uint *arr, size_t N) { sort(arr, arr + N); },
    [](uint *arr, size_t N) { qsort(arr, N, sizeof(uint), utils::compare_uint); },
    insertion_sort,
    merge_sort,
    quick_sort,
    randomized_quick_sort,
    heap_sort,
    radix_sort,
    [](uint *arr, size_t N) { bucket_sort(arr, N, 1U, 1000U); },
};

typedef uint *(*gen_func_t)();
default_random_engine GEN;
const vector<string> DIST_NAMES{"Uniform",     "Gaussian",     "Degenerate",
                                "Left skewed", "Right skewed", "Discrete"};
const vector<gen_func_t> GEN_FUNCS{
    // Uniform
    []() { return utils::new_random_array(N, 1U, 1000U); },
    // Gaussian
    []() {
      normal_distribution<double> dist(500, 5);
      uint *arr = new uint[N];
      for (int i = 0; i < N; i++)
        do {
          arr[i] = round(dist(GEN));
        } while (arr[i] < 1 || arr[i] > 1000);
      return arr;
    },
    // Degenerate
    []() {
      uint *arr = new uint[N];
      for (int i = 0; i < N; i++)
        arr[i] = 500;
      return arr;
    },
    // Left skewed
    []() {
      exponential_distribution<double> dist(1.0 / 50);
      uint *arr = new uint[N];
      for (int i = 0; i < N; i++)
        do {
          arr[i] = 1 + floor(dist(GEN));
        } while (arr[i] > 1000);
      return arr;
    },
    // Right skewed
    []() {
      exponential_distribution<double> dist(1.0 / 50);
      uint *arr = new uint[N];
      for (int i = 0; i < N; i++)
        do {
          arr[i] = 1000 - floor(dist(GEN));
        } while (arr[i] < 1);
      return arr;
    },
    // Discrete
    []() {
      uint *arr = new uint[N];
      for (int i = 0; i < N; i++)
        arr[i] = (rand() % 10 + 1) * 100;
      return arr;
    }};

double evaluate(const string &name, void (*sort_func)(uint *, size_t),
                const uint *arr, size_t N) {
  uint *arr_copy = new uint[N];
  memcpy(arr_copy, arr, sizeof(uint) * N);
  utils::timer.reset();
  sort_func(arr_copy, N);
  return utils::timer.seconds();
}

int main() {
  srand(RAND_SEED);
  // keys: (dist, repeat), values: times of each sort function
  map<pair<string, int>, vector<double>> times;
  // keys: dist, values: histogram data
  map<string, vector<size_t>> hist_data;
  for (int i = 0; i < GEN_FUNCS.size(); i++) {
    uint *arr = GEN_FUNCS[i]();
    hist_data[DIST_NAMES[i]] = vector<size_t>(1000);
    for (int j = 0; j < N; j++)
      hist_data[DIST_NAMES[i]][arr[j] - 1]++;
    for (int r = 0; r < REPEAT; r++) {
      utils::shuffle(arr, N);
      for (int j = 0; j < SORT_FUNCS.size(); j++) {
        double time = evaluate(SORT_NAMES[j], SORT_FUNCS[j], arr, N);
        times[{DIST_NAMES[i], r}].push_back(time);
        cout << DIST_NAMES[i] << ", " << r + 1 << " / " << REPEAT << ", ";
        cout << SORT_NAMES[j] << ": " << time << " s" << endl;
      }
    }
    delete[] arr;
    cout << endl;
  }
  utils::save_csv("../data/lab1_main2_hist.csv", hist_data);
  utils::save_csv("../data/lab1_main2.csv", times);
  return 0;
}