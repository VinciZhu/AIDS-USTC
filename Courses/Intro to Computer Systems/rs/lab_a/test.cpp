#include <iostream>
#include <sstream>
using namespace std;
int main() {
  string a("  Hello World!   "), b;
  char c;
  istringstream ss(a);
  while(ss >> c) {
    cout << c << endl;
  }
  cout << a;
  return 0;
}