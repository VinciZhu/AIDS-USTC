#include <iostream>
#define MAX_SIZE 200
using namespace std;
int main() {
  int k, m, pw[MAX_SIZE + 1], next[MAX_SIZE + 1];
  cout << "输入约瑟夫环的长度：";
  cin >> k;
  cout << "请输入m的初始值 m:";
  cin >> m;
  cout << "请输入每个人的密码:" << endl;
  for (int i = 1; i <= k; i++) {
    cin >> pw[i];
    next[i] = i + 1;
  }
  next[k] = 1;
  int a = k;
  for (int i = 0; i < k; i++) {
    m = (m - 1) % (k - i) + 1;
    for (int j = 1; j < m; j++) {
      a = next[a];
    }
    int temp = next[a];
    next[a] = next[temp];
    a = temp;
    m = pw[a];
    cout << a << endl;
  }
  return 0;
}