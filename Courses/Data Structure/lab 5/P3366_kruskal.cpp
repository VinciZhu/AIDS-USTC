#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;
using edge = tuple<int, int, int>;
int N, M;
set<edge> E;

void init() {
  cin >> N >> M;
  int u, v, w;
  for (int i = 0; i < M; i++) {
    cin >> u >> v >> w;
    E.insert({w, u - 1, v - 1});
  }
}

void kruskal() {
  int s = 0, c = 0;
  vector<int> pa(N), siz(N, 1);
  iota(pa.begin(), pa.end(), 0);
  for (auto e : E) {
    int u = get<1>(e), v = get<2>(e);
    while (pa[u] != pa[pa[u]]) pa[u] = pa[pa[u]];
    while (pa[v] != pa[pa[v]]) pa[v] = pa[pa[v]];
    if (pa[u] != pa[v]) {
      c++;
      s += get<0>(e);
      if (siz[pa[u]] < siz[pa[v]]) swap(u, v);
      pa[v] = pa[pa[v]] = pa[u];
      siz[u] += siz[v];
    }
  }
  if (c == N - 1)
    cout << s << endl;
  else
    cout << "orz" << endl;
}

int main() {
  init();
  kruskal();
  return 0;
}