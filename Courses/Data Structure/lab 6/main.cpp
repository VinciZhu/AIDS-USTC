#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

size_t Hash(const string &s) {
  return ((s.front() - 'a') * 100 + (s.back() - 'a')) % 41;
}
size_t Hash2(const string &s) {
  return ((s.front() - 'a') * 100 + (s.back() - 'a')) % 7 + 1;
}

class hashTable : public vector<string> {
 public:
  enum collisionSolution { linearProbing, quadraticProbing, doubleHashing };
  bool find_flag;
  hashTable(size_t _size, collisionSolution _solutionType = linearProbing)
      : vector<string>(_size), solutionType(_solutionType) {
    find_flag = false;
  };
  size_t insert(const string &s);
  size_t search(const string &s);
  size_t collision_count(const string &s);

 private:
  collisionSolution solutionType;
  size_t next_index(const string &s, size_t count) const;
};

size_t hashTable::insert(const string &s) {
  size_t index = search(s);
  at(index) = s;
  return index;
}

size_t hashTable::search(const string &s) {
  size_t index = Hash(s);
  size_t count = 0;
  while (at(index) != "" && at(index) != s) index = next_index(s, ++count);
  find_flag = !at(index).empty();
  return index;
}

size_t hashTable::collision_count(const string &s) {
  size_t index = Hash(s);
  size_t count = 0;
  while (at(index) != "" && at(index) != s) index = next_index(s, ++count);
  return count;
}

size_t hashTable::next_index(const string &s, size_t count) const {
  int d = 0;
  switch (solutionType) {
    case linearProbing:
      d = count;
      break;
    case quadraticProbing:
      d *= d = (count + 1) / 2;
      d *= (count % 2 * 2 - 1);
      d += size() * size();
      break;
    case doubleHashing:
      d = count * Hash2(s);
      break;
  }
  return (Hash(s) + d) % size();
}

// hashTable key(43, hashTable::linearProbing);
// hashTable key(43, hashTable::quadraticProbing);
hashTable key(43, hashTable::doubleHashing);
map<string, vector<int>> count;

void scan_file(const string &filename) {
  ifstream in(filename);
  string s, word;
  count.insert({filename, vector<int>(43, 0)});
  int index;
  while (!in.eof()) {
    getline(in, s);
    s += ' ';
    for (char c : s) {
      if (islower(c))
        word += c;
      else if (word != "") {
        index = key.search(word);
        if (key.find_flag) count[filename][index]++;
        word = "";
      }
    }
  }
}

int dot(const vector<int> &a, const vector<int> &b) {
  int sum = 0;
  for (int i = 0; i < 43; i++) sum += a[i] * b[i];
  return sum;
}

double len(const vector<int> &a) { return sqrt(dot(a, a)); }

double cos(const vector<int> &a, const vector<int> &b) {
  return dot(a, b) / (len(a) * len(b));
}

vector<double> norm(const vector<int> &a) {
  double l = len(a);
  vector<double> b(43);
  for (int i = 0; i < 43; i++) b[i] = 1.0 * a[i] / l;
  return b;
}

double dis(const vector<double> &a, const vector<double> &b) {
  double sum = 0;
  for (int i = 0; i < 43; i++) sum += (a[i] - b[i]) * (a[i] - b[i]);
  return sqrt(sum);
}

void cmp_file(const string &f1, const string &f2) {
  double r = cos(count[f1], count[f2]),
         d = dis(norm(count[f1]), norm(count[f2]));
  cout << f1 << "和" << f2 << "的相似情况为："
       << "相似度：" << r << "\t几何距离：" << d;
  if (r < 0.85)
    cout << "\t这两个文件内容不相似";
  else if (d > 0.25)
    cout << "\t这两个文件内容可能不相似";
  else
    cout << "\t这两个文件内容确实可能相似";
  cout << endl;
}

int main() {
  ifstream fin("keyword.txt");
  string s;
  while (!fin.eof()) {
    getline(fin, s);
    key.insert(s);
  }
  fin.close();
  vector<string> filename{"test1.cpp", "test2.cpp", "test3.cpp", "test4.cpp"};
  for (auto &f : filename) scan_file(f);
  int c = 0, l, sum = 0, index;
  cout << left;
  for (auto &s : key)
    if (s != "") {
      c++;
      index = key.search(s);
      sum += l = key.collision_count(s) + 1;
      cout << setw(16) << s;
      cout << setw(4) << index << setw(8) << l;
      for (auto &f : filename) cout << setw(4) << count[f][index];
      cout << endl;
    }
  cout << setw(28) << "Average search length:" << 1.0 * sum / c << endl;
  for (int i = 0; i < filename.size(); i++)
    for (int j = i + 1; j < filename.size(); j++)
      cmp_file(filename[i], filename[j]);
  return 0;
}