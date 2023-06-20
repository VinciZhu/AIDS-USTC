#include "sort.hpp"
#include "utils.hpp"

const uint RAND_SEED = 42;
const size_t N = 20;

void test(const string &name, void (*sort_func)(uint *, size_t),
          const uint *arr, const uint *arr_sorted, size_t N) {
  uint *arr_copy = new uint[N];
  memcpy(arr_copy, arr, sizeof(uint) * N);
  sort_func(arr_copy, N);
  cout << name << ":" << endl;
  utils::print_array(arr_copy, N);
  if (memcmp(arr_sorted, arr_copy, sizeof(uint) * N))
    throw runtime_error("Incorrect result of " + name);
  delete[] arr_copy;
}

int main() {
  srand(RAND_SEED);
  try {
    uint *arr = utils::new_random_array(N);
    uint *arr_sorted = new uint[N];

    memcpy(arr_sorted, arr, sizeof(uint) * N);
    sort(arr_sorted, arr_sorted + N); // std::sort
    cout << "Random array:" << endl;
    utils::print_array(arr, N);

    test("Insertion sort", insertion_sort, arr, arr_sorted, N);
    test("Merge sort", merge_sort, arr, arr_sorted, N);
    test("Quick sort", quick_sort, arr, arr_sorted, N);
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