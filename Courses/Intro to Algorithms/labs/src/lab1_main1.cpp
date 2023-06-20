#include "sort.hpp"
#include "utils.hpp"

const uint RAND_SEED = 42;
const int REPEAT = 5;
const vector<size_t> N{50000,  100000, 150000, 200000, 250000,
                       300000, 350000, 400000, 450000, 500000};
// const vector<size_t> N{500,  1000, 1500, 2000, 2500,
//                        3000, 3500, 4000, 4500, 5000};

const vector<string> SORT_NAMES{
    "sort",       "qsort",      "Insertion sort",
    "Merge sort", "Quick sort", "Randomized quick sort",
    "Heap sort",  "Radix sort", "Bucket sort"};
const vector<sort_func_t> SORT_FUNCS{
    [](uint *arr, size_t N) { sort(arr, arr + N); },
    [](uint *arr, size_t N) {
      qsort(arr, N, sizeof(uint), utils::compare_uint);
    },
    insertion_sort,
    merge_sort,
    quick_sort,
    randomized_quick_sort,
    heap_sort,
    radix_sort,
    [](uint *arr, size_t N) { bucket_sort(arr, N, 1U, 1000U); },
};

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
  // keys: (N, repeat), values: times of each sort function
  map<pair<size_t, int>, vector<double>> times;
  for (size_t n : N) {
    for (int r = 0; r < REPEAT; r++) {
      uint *arr = utils::new_random_array(n);
      for (size_t i = 0; i < SORT_FUNCS.size(); i++) {
        double time = evaluate(SORT_NAMES[i], SORT_FUNCS[i], arr, n);
        times[{n, r}].push_back(time);
        cout << "N = " << n << ", " << r + 1 << " / " << REPEAT << ", ";
        cout << SORT_NAMES[i] << ": " << time << " s" << endl;
      }
      delete[] arr;
    }
    cout << endl;
  }
  utils::save_csv("../data/lab1_main1.csv", times);
  return 0;
}