#include "sort.hpp"
#include "utils.hpp"

const uint RAND_SEED = 42;
const size_t N = 1000;

bool compare_by_loop(const uint *arr, const uint *arr_sorted, size_t N) {
  for (size_t i = 0; i < N; i++)
    if (arr[i] != arr_sorted[i])
      return false;
  return true;
}

void test(const string &name, void (*sort_func)(uint *, size_t),
          const uint *arr, const uint *arr_sorted, size_t N) {
  uint *arr_copy = new uint[N];
  memcpy(arr_copy, arr, sizeof(uint) * N);
  utils::timer.reset();
  sort_func(arr_copy, N);
  cout << name << ": " << utils::timer.seconds() << " s, ";
  bool correct = compare_by_loop(arr_sorted, arr_copy, N);
  cout << (correct ? "True" : "False") << endl;
  utils::print_array(arr_copy, N);
  if (!correct)
    throw runtime_error("Incorrect result of " + name);
  delete[] arr_copy;
}

int main() {
  srand(RAND_SEED);
  try {
    uint *arr = utils::new_random_array(N);
    uint *arr_sorted = new uint[N];
    bool correct;

    cout << "Random array:" << endl;
    utils::print_array(arr, N);

    memcpy(arr_sorted, arr, sizeof(uint) * N);
    utils::timer.reset();
    insertion_sort(arr_sorted, N);
    cout << "Insertion sort: " << utils::timer.seconds() << " s" << endl;
    utils::print_array(arr_sorted, N);

    test("Merge sort", merge_sort, arr, arr_sorted, N);
    test("Quick sort", quick_sort, arr, arr_sorted, N);
    test("Randomized quick sort", randomized_quick_sort, arr, arr_sorted, N);
    test("Heap sort", heap_sort, arr, arr_sorted, N);
    test("Radix sort", radix_sort, arr, arr_sorted, N);
    test(
        "Bucket sort",
        [](uint *arr, size_t N) { bucket_sort(arr, N, 1U, 1000U); }, arr,
        arr_sorted, N);

    delete[] arr;
    delete[] arr_sorted;
  } catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
    return 1;
  }
  return 0;
}