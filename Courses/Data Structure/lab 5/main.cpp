#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#define DBL_MAX double(1.79769313486231570814527423731704357e+308L)

using namespace std;
using out_edge = pair<double, int>;
using adj_list = list<out_edge>;
using graph = vector<adj_list>;
using edge = tuple<double, int, int>;

graph G;
set<edge> E;
int N, M;

void init() {
  ifstream fin("data.txt");
  fin >> N >> M;
  G.resize(N);
  int u, v;
  double w;
  for (int i = 0; i < M; i++) {
    fin >> u >> v >> w;
    G[u].push_back({w, v});
    if (u != v) G[v].push_back({w, u});
    E.insert({w, u, v});
  }
  fin.close();
}

void dfs() {
  cout << "depth first traverse:" << endl;
  stack<int> s;
  vector<bool> vis(N, false);
  int c = 0, u, v;
  for (int i = 0; i < N; i++)
    if (!vis[i]) {
      s.push(i);
      vis[i] = true;
      while (!s.empty()) {
        u = s.top();
        cout << u << ' ';
        s.pop();
        for (out_edge& e : G[u]) {
          v = e.second;
          if (!vis[v]) {
            s.push(v);
            vis[v] = true;
          }
        }
      }
      c++;
      cout << endl;
    }
  cout << "there are " << c << " connected components" << endl;
}

void bfs() {
  cout << "breadth first traverse:" << endl;
  queue<int> q;
  vector<bool> vis(N, false);
  int c = 0, u, v;
  for (int i = 0; i < N; i++)
    if (!vis[i]) {
      q.push(i);
      vis[i] = true;
      while (!q.empty()) {
        u = q.front();
        cout << u << ' ';
        q.pop();
        for (out_edge& e : G[u]) {
          v = e.second;
          if (!vis[v]) {
            q.push(v);
            vis[v] = true;
          }
        }
      }
      c++;
      cout << endl;
    }
  cout << "there are " << c << " connected components" << endl;
}

void prim() {
  cout << "prim's minimal spanning forest:" << endl;
  vector<bool> vis(N, false);
  vector<double> dis(N, DBL_MAX);
  vector<int> pre(N, -1);
  set<out_edge> h;
  int u, v;
  for (int i = 0; i < N; i++)
    if (!vis[i]) {
      h.insert({dis[i], i});
      while (!h.empty()) {
        u = h.begin()->second;
        h.erase(h.begin());
        if (!vis[u]) {
          if (pre[u] != -1) cout << '(' << pre[u] << ',' << u << ')' << endl;
          vis[u] = true;
          for (out_edge& e : G[u]) {
            v = e.second;
            if (!vis[v] && e.first < dis[v]) {
              dis[v] = e.first;
              pre[v] = u;
              h.insert({dis[v], v});
            }
          }
        }
      }
    }
}

void kruskal() {
  cout << "kruskal's minimal spanning forest:" << endl;
  vector<int> pa(N), siz(N, 1);
  iota(pa.begin(), pa.end(), 0);
  for (auto e : E) {
    int u = get<1>(e), v = get<2>(e);
    while (pa[u] != pa[pa[u]]) pa[u] = pa[pa[u]];
    while (pa[v] != pa[pa[v]]) pa[v] = pa[pa[v]];
    if (pa[u] != pa[v]) {
      cout << '(' << u << ',' << v << ')' << endl;
      if (siz[pa[u]] < siz[pa[v]]) swap(u, v);
      pa[v] = pa[pa[v]] = pa[u];
      siz[u] += siz[v];
    }
  }
}

int main() {
  init();
  dfs();
  bfs();
  prim();
  kruskal();
  return 0;
}