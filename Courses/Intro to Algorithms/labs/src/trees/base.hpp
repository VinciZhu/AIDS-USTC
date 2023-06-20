#pragma once
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

template <typename T> class SearchTreeInterface {
public:
  virtual ~SearchTreeInterface() = default;
  virtual void clear() = 0;
  virtual void insert(const T &value) = 0;
  virtual void remove(const T &value) = 0;
  virtual bool contains(const T &value) const = 0;
  virtual bool check() const { return true; }
  virtual int height() const = 0;
  virtual int size() const = 0;
  virtual bool empty() const = 0;
  virtual vector<T> values() const = 0;
  virtual void print(ostream &os = cout, const string& indent = "") const = 0;
  virtual void print_csv(ostream &os = cout, const string& indent = "") const = 0;
  virtual void save_csv(const string &filename) const {
    ofstream file(filename);
    print_csv(file);
    file.close();
  }
};