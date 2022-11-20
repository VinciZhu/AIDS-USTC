#include <cstring>
#include <fstream>
#include <iostream>
#define MAX_SIZE 255
using namespace std;
int main() {
  ifstream input;
  string filename;
  char keyword[MAX_SIZE], cur_line[MAX_SIZE];
  int l, next[MAX_SIZE], cnt = 0, ans = 0;
  /* Input */
  cout << "输入文件" << endl;
  getline(cin, filename);
  cout << "输入目标关键字" << endl;
  cin.getline(keyword, 255);
  l = strlen(keyword);
  /* Get next array */
  next[0] = -1;
  for (int i = 1; keyword[i]; ++i) {
    int j = next[i - 1];
    while (j >= 0 && keyword[i - 1] != keyword[j]) j = next[j];
    next[i] = j + 1;
  }
  /* Process */
  input.open(filename);
  while (!input.eof()) {
    input.getline(cur_line, 255);
    ++cnt;
    int j = 0;
    bool f = false;
    for (int i = 0; cur_line[i]; ++i) {
      while (j >= 0 && cur_line[i] != keyword[j]) j = next[j];
      ++j;
      if (j == l) {
        ++ans;
        j = 0;
        f = true;
      }
    }
    if (f) cout << cnt << ' ' << cur_line << endl;
  }
  cout << "\'" << keyword << "\'共出现 " << ans << " 次";
  return 0;
}