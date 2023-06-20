#pragma once
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <random>
#include <vector>

namespace utils {
using namespace std;

template <typename T> int lower_bound(T *array, int l, int r, const T &key) {
  while (l < r) {
    int m = (l + r) / 2;
    if (array[m] < key)
      l = m + 1;
    else
      r = m;
  }
  return l;
}

template <typename T> int upper_bound(T *array, int l, int r, const T &key) {
  while (l < r) {
    int m = (l + r) / 2;
    if (array[m] <= key)
      l = m + 1;
    else
      r = m;
  }
  return l;
}

template <typename T> int lower_bound(T *array, size_t size, const T &key) {
  return lower_bound(array, 0, size, key);
}

template <typename T> int upper_bound(T *array, size_t size, const T &key) {
  return upper_bound(array, 0, size, key);
}

int compare_uint(const void *a, const void *b) { return *(uint *)a - *(uint *)b; }

uint *new_random_array(int n, uint min_val = 1, uint max_val = 1000) {
  uint *arr = new uint[n];
  for (int i = 0; i < n; i++)
    arr[i] = rand() % (max_val - min_val + 1) + min_val;
  return arr;
}

double *new_random_array(int n, double min_val, double max_val) {
  double *arr = new double[n];
  for (int i = 0; i < n; i++)
    arr[i] = (double)rand() / RAND_MAX * (max_val - min_val) + min_val;
  return arr;
}

float *new_random_array(int n, float min_val, float max_val) {
  float *arr = new float[n];
  for (int i = 0; i < n; i++)
    arr[i] = (float)rand() / RAND_MAX * (max_val - min_val) + min_val;
  return arr;
}

template <typename T> void shuffle(T *arr, int n) {
  for (int i = 0; i < n; i++) {
    int j = rand() % n;
    swap(arr[i], arr[j]);
  }
}

template <typename T> void print_array(T *arr, int n) {
  if (n > 50) {
    for (int i = 0; i < 25; i++)
      cout << arr[i] << " ";
    cout << "... ";
    for (int i = n - 25; i < n; i++)
      cout << arr[i] << " ";
  } else
    for (int i = 0; i < n; i++)
      cout << arr[i] << " ";
  cout << endl;
}

template <typename T> void print_array(const vector<T> &arr) {
  print_array(arr.data(), arr.size());
}

struct Timer {
  chrono::high_resolution_clock::time_point start;
  Timer() { reset(); }
  void reset() { start = chrono::high_resolution_clock::now(); }
  double seconds() {
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::duration<double>>(end - start).count();
  }
  double milliseconds() { return seconds() * 1000; }
} timer;

template <typename K, typename V>
void save_csv(const string &filename, const map<K, vector<V>> &m) {
  ofstream file(filename);
  if (!file.is_open())
    throw runtime_error("Cannot open file " + filename);
  for (const auto &kv : m) {
    file << kv.first;
    for (const auto &v : kv.second)
      file << "," << v;
    file << endl;
  }
}

template <typename K1, typename K2, typename V>
void save_csv(const string &filename, const map<pair<K1, K2>, vector<V>> &m) {
  ofstream file(filename);
  if (!file.is_open())
    throw runtime_error("Cannot open file " + filename);
  for (const auto &kv : m) {
    file << kv.first.first << "," << kv.first.second;
    for (const auto &v : kv.second)
      file << "," << v;
    file << endl;
  }
}

template <typename... Ks, typename V>
void save_csv(const string &filename, const map<tuple<Ks...>, vector<V>> &m) {
  ofstream file(filename);
  if (!file.is_open())
    throw runtime_error("Cannot open file " + filename);
  for (const auto &kv : m) {
    file << get<0>(kv.first);
    for (size_t i = 1; i < sizeof...(Ks); i++)
      file << "," << get<i>(kv.first);
    for (const auto &v : kv.second)
      file << "," << v;
    file << endl;
  }
}

} // namespace utils