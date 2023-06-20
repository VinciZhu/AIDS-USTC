#pragma once
#include "linked_list.hpp"
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

typedef void (*sort_func_t)(uint *, size_t);

// Insertion sort
template <typename T> void insertion_sort(T *array, size_t size) {
  for (int i = 1; i < size; i++) {
    T key = array[i];
    int j = i;
    while (j > 0 && array[j - 1] > key)
      array[j--] = array[j - 1];
    array[j] = key;
  }
}

// Merge sort
template <typename T> void merge_sort(T *array, int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
    merge_sort(array, l, m);
    merge_sort(array, m + 1, r);

    // merge
    int n1 = m - l + 1, n2 = r - m;
    int *L = new int[n1], *R = new int[n2];
    memcpy(L, array + l, sizeof(int) * n1);
    memcpy(R, array + m + 1, sizeof(int) * n2);

    int i = 0, j = 0, k = l;
    while (i < n1 || j < n2)
      if (j >= n2 || i < n1 && L[i] <= R[j])
        array[k++] = L[i++];
      else
        array[k++] = R[j++];

    delete[] L;
    delete[] R;
  }
};

template <typename T> void merge_sort(T *array, size_t size) {
  merge_sort(array, 0, size - 1);
}

// Quick sort
// https://www.geeksforgeeks.org/quick-sort-vs-merge-sort/
template <typename T>
void quick_sort(T *array, int l, int r, bool random = false) {
  while (l < r) {
    // partition
    if (random)
      swap(array[l + rand() % (r - l + 1)], array[r]);
    T pivot = array[r];
    int i = l;
    for (int j = l; j < r; j++)
      if (array[j] < pivot)
        swap(array[i++], array[j]);
    swap(array[i], array[r]);

    if (i - l < r - i) {
      quick_sort(array, l, i - 1);
      l = i + 1;
    } else {
      quick_sort(array, i + 1, r);
      r = i - 1;
    }
  }
}

template <typename T> void quick_sort(T *array, size_t size) {
  quick_sort(array, 0, size - 1, false);
}

template <typename T> void randomized_quick_sort(T *array, size_t size) {
  quick_sort(array, 0, size - 1, true);
}

// Heap sort
template <typename T> void heap_sort(T *array, size_t size) {
  auto heapify = [&](int i, int n) {
    int l, r, largest = i;
    do {
      i = largest;
      l = 2 * i + 1;
      r = 2 * i + 2;
      if (l < n && array[l] > array[largest])
        largest = l;
      if (r < n && array[r] > array[largest])
        largest = r;
      swap(array[i], array[largest]);
    } while (largest != i);
  };

  for (int i = size / 2 - 1; i >= 0; i--)
    heapify(i, size);

  for (int i = size - 1; i >= 0; i--) {
    swap(array[0], array[i]);
    heapify(0, i);
  }
}

// Radix sort
void radix_sort(uint *array, size_t size) {
  for (int i = 0; i < 4; i++) {
    vector<uint> count(256);
    for (int j = 0; j < size; j++)
      count[(array[j] >> (i * 8)) & 0xff]++;
    for (int j = 1; j < 256; j++)
      count[j] += count[j - 1];
    vector<uint> temp(size);
    for (int j = size - 1; j >= 0; j--)
      temp[--count[(array[j] >> (i * 8)) & 0xff]] = array[j];
    memcpy(array, temp.data(), sizeof(uint) * size);
  }
}

// Bucket sort
template <typename T>
void bucket_sort(T *array, size_t size, T min_val, T max_val) {
  vector<LinkedList<T>> buckets(size + 1);
  auto hash = [&](T val) {
    return floor(1.0 * (val - min_val) / (max_val - min_val) * size);
  };
  for (int i = 0; i < size; i++)
    buckets[hash(array[i])].push_back(array[i]);

  for (auto &bucket : buckets)
    insertion_sort(bucket);

  int k = 0;
  for (auto &bucket : buckets)
    for (auto e : bucket)
      array[k++] = e;
}