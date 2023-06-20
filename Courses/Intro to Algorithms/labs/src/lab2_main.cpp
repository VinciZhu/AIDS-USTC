#include "trees.hpp"
#include "utils.hpp"

const vector<uint> SEEDS{111, 222, 333, 444, 555};
const vector<size_t> N{10000, 20000, 30000, 40000, 50000,
                       60000, 70000, 80000, 90000, 100000};

using DataType = float;
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

const DataType MIN_VAL = 10, MAX_VAL = 99;

size_t indent = 0;
string prefix() { return string(indent * 2, ' ') + "> "; }

int main() {
  // keys: (n, seed), values: elapsed times of each tree
  map<pair<size_t, uint>, vector<double>> insert_times;
  map<pair<size_t, uint>, vector<double>> search_times;
  map<pair<size_t, uint>, vector<double>> delete_times;

  double t;
  // enumerate seeds
  for (uint seed : SEEDS) {
    srand(seed);
    cout << prefix() << "Seed: " << seed << endl;
    ++indent;
    // enumerate sizes
    for (uint n : N) {
      DataType *arr = utils::new_random_array(n, MIN_VAL, MAX_VAL);
      uint del_id[n];
      iota(del_id, del_id + n, 0);
      utils::shuffle(del_id, n);
      cout << prefix() << "Size: " << n << endl;
      ++indent;
      // enumerate trees
      for (int i = 0; i < TREES.size(); i++) {
        cout << prefix() << NAMES[i] << ':' << endl;
        auto &tree = *TREES[i];
        ++indent;

        // insert
        utils::timer.reset();
        for (int j = 0; j < n; j++)
          tree.insert(arr[j]);
        t = utils::timer.seconds();
        insert_times[{n, seed}].push_back(t);
        cout << prefix() << "Insertion time: " << t << endl;

        // insert check
        if (!tree.check())
          throw runtime_error("Tree check failed!");
        if (tree.size() != n)
          throw runtime_error("Tree size mismatch!");

        // search
        utils::timer.reset();
        for (int j = 0; j < n; j++)
          tree.contains(arr[j]);
        t = utils::timer.seconds();
        search_times[{n, seed}].push_back(t);
        cout << prefix() << "Search time: " << t << endl;

        // delete
        utils::timer.reset();
        for (int j = 0; j < n; j++)
          tree.remove(arr[j]);
        t = utils::timer.seconds();
        delete_times[{n, seed}].push_back(t);
        cout << prefix() << "Deletion time: " << t << endl;

        // delete check
        if (!tree.empty())
          throw runtime_error("Tree not empty!");

        --indent;
      }
      delete[] arr;
      --indent;
    }
    --indent;
  }
  utils::save_csv("../data/lab2_main_insert.csv", insert_times);
  utils::save_csv("../data/lab2_main_search.csv", search_times);
  utils::save_csv("../data/lab2_main_delete.csv", delete_times);
  return 0;
}
