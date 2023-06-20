#include "trees.hpp"
#include "utils.hpp"

using DataType = uint;
// clang-format off
const vector<string> NAMES {
  "Binary Search Tree", 
  "AVL Tree", 
  "Red-Black Tree",
  "B Tree", 
  "B+ Tree"
};
const vector<SearchTreeInterface<DataType> *> TREES {
    new BinarySearchTree<DataType>, 
    new AVLTree<DataType>,
    new RedBlackTree<DataType>, 
    new BTree<DataType, 5>, 
    new BPlusTree<DataType, 5>
};
// clang-format on

const uint RAND_SEED = 42;

// const DataType MIN_VAL = 0, MAX_VAL = 1000;
// const size_t N = 1000, M = 20;
// const int VERBOSE = 0;

const DataType MIN_VAL = 10, MAX_VAL = 99;
const size_t N = 1145, M = 10;
const int VERBOSE = 0;

size_t indent = 0;
string prefix() { return string(indent * 2, ' ') + "> "; }

void print_tree_info(SearchTreeInterface<DataType> &tree) {
  if (VERBOSE > 1) {
    cout << prefix() << "Size / Height: " << tree.size() << " / "
         << tree.height() << endl;
    cout << prefix() << "Values: ";
    utils::print_array(tree.values());
  }
  if (VERBOSE > 2) {
    cout << prefix() << "Structure: " << endl;
    ++indent;
    tree.print(cout, prefix());
    --indent;
  }
}

void insert_element(SearchTreeInterface<DataType> &tree, DataType val) {
  if (VERBOSE > 0) {
    cout << prefix() << left << setw(20)
         << "insert_element(" + to_string(val) + ")" << '\t';
    utils::timer.reset();
  }
  tree.insert(val);
  if (VERBOSE > 0)
    cout << utils::timer.milliseconds() << "ms" << endl;
  indent++;
  print_tree_info(tree);
  indent--;
}

void search_element(SearchTreeInterface<DataType> &tree, DataType val) {
  if (VERBOSE > 0) {
    cout << prefix() << left << setw(20)
         << "search_element(" + to_string(val) + ")" << '\t';
    utils::timer.reset();
  }
  bool found = tree.contains(val);
  if (VERBOSE > 0)
    cout << utils::timer.milliseconds() << "ms" << endl;
  indent++;
  if (VERBOSE > 1) {
    cout << prefix() << "Found: " << (found ? "true" : "false") << endl;
  }
  if (!found)
    throw runtime_error("Value not found!");
  indent--;
}

void delete_element(SearchTreeInterface<DataType> &tree, DataType val) {
  if (VERBOSE > 0) {
    utils::timer.reset();
    cout << prefix() << left << setw(20)
         << "delete_element(" + to_string(val) + ")" << '\t';
  }
  tree.remove(val);
  if (VERBOSE > 0)
    cout << utils::timer.milliseconds() << "ms" << endl;
  indent++;
  print_tree_info(tree);
  indent--;
}

void check_tree(SearchTreeInterface<DataType> &tree, size_t size,
                const DataType *arr = nullptr) {
  if (VERBOSE > 0) {
    utils::timer.reset();
    cout << prefix() << left << setw(20)
         << "check_tree(" + to_string(size) + ")" << '\t';
  }
  bool valid = tree.check();
  int tree_size = tree.size();
  if (VERBOSE > 0)
    cout << utils::timer.milliseconds() << "ms" << endl;
  indent++;
  if (arr != nullptr || VERBOSE > 1) {
    cout << prefix() << "Valid: " << (valid ? "true" : "false") << endl;
    cout << prefix() << "Size: " << tree_size
         << (tree_size == size ? " (OK)" : " (FAIL)") << endl;
  }
  if (!valid)
    throw runtime_error("Tree check failed!");
  if (tree_size != size)
    throw runtime_error("Tree size mismatch!");

  if (arr != nullptr) {
    vector<DataType> values = tree.values();
    cout << prefix() << "Values: ";
    bool same = true;
    for (int i = 0; i < size; i++) {
      if (values[i] != arr[i])
        same = false;
      cout << values[i] << ' ';
    }
    cout << (same ? "(OK)" : "(FAIL)") << endl;
    cout << prefix() << "Structure: " << endl;
    ++indent;
    tree.print(cout, prefix());
    --indent;
    if (!same)
      throw runtime_error("Tree values mismatch!");
  }
  indent--;
}

void test_tree(const string &name, SearchTreeInterface<DataType> &tree,
               const DataType *arr, const DataType *subarr, const uint *del_id,
               size_t N) {
  const string &filename = "../data/lab2_test_" + name + ".csv";
  cout << prefix() << "Testing " << name << "..." << endl;
  ++indent;
  // Insert all elements
  cout << prefix() << "Inserting " << N << " elements..." << endl;
  ++indent;
  for (int i = 0; i < N; i++)
    insert_element(tree, arr[i]);
  check_tree(tree, N);
  --indent;
  // Search each element
  cout << prefix() << "Searching each element..." << endl;
  ++indent;
  for (int i = 0; i < N; i++)
    search_element(tree, arr[i]);
  --indent;
  // Delete last N - M elements
  cout << prefix() << "Deleting last " << N - M << " elements..." << endl;
  ++indent;
  for (int i = 0; i < N - M; i++)
    delete_element(tree, arr[del_id[i]]);
  tree.save_csv(filename);
  --indent;
  cout << prefix() << "CSV saved to " << filename << endl;
  if (VERBOSE > 1) {
    ++indent;
    tree.print_csv(cout, prefix());
    --indent;
  }
  check_tree(tree, M, subarr);
  // Delete remaining elements
  cout << prefix() << "Deleting remaining " << M << " elements..." << endl;
  ++indent;
  for (int i = 0; i < M; i++)
    delete_element(tree, arr[i]);
  check_tree(tree, 0);
  --indent;
  --indent;
}

template <typename T>
void test_all(const vector<string> &names,
              const vector<SearchTreeInterface<T> *> &trees, const T &min_val,
              const T &max_val, size_t N, size_t M, uint rand_seed,
              int verbose) {
  srand(rand_seed);
  T *arr = utils::new_random_array(N, min_val, max_val);
  utils::print_array(arr, N);

  cout << prefix() << "First " << M << " elements: ";
  T *subarr = new T[M];
  memcpy(subarr, arr, M * sizeof(T));
  sort(subarr, subarr + M);
  utils::print_array(subarr, M);

  uint del_id[N - M];
  iota(del_id, del_id + N - M, M);
  utils::shuffle(del_id, N - M);

  for (int i = 0; i < trees.size(); i++)
    test_tree(names[i], *trees[i], arr, subarr, del_id, N);

  delete[] arr;
  delete[] subarr;
}

int main() {
  try {
    test_all(NAMES, TREES, MIN_VAL, MAX_VAL, N, M, RAND_SEED, VERBOSE);
  } catch (const exception &e) {
    cerr << endl << "ERROR: " << e.what() << endl << endl;
    return 1;
  }
  return 0;
}