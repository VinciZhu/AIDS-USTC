#include <climits>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;
using out_edge = pair<int, int>;
using adj_list = list<out_edge>;
using graph = vector<adj_list>;

graph G;
int N, M;

void init() {
  cin >> N >> M;
  G.resize(N);
  int u, v, w;
  for (int i = 0; i < M; i++) {
    cin >> u >> v >> w;
    G[u - 1].push_back({w, v - 1});
    if (u != v) G[v - 1].push_back({w, u - 1});
  }
}

void prim() {
  int s = 0, c = 0;
  vector<bool> vis(N, false);
  vector<int> dis(N, INT_MAX);
  set<out_edge> h;
  int u, v;
  dis[s] = 0;
  h.insert({0, 0});
  while (c < N && !h.empty()) {
    u = h.begin()->second;
    h.erase(h.begin());
    if (!vis[u]) {
      c++;
      s += dis[u];
      vis[u] = true;
      for (out_edge& e : G[u]) {
        v = e.second;
        if (!vis[v] && e.first < dis[v]) {
          dis[v] = e.first;
          h.insert({dis[v], v});
        }
      }
    }
  }
  if (c == N)
    cout << s << endl;
  else
    cout << "orz" << endl;
}

int main() {
  init();
  prim();
  return 0;
}