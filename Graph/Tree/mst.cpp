#include <bits/stdc++.h>
using namespace std;

const int N = 500005;

int n, m;

vector<pair<int, pair<int, int>>> edges;

vector<pair<int,int>> mst[N];

int uf[N];

void builduf(){
  for(int i = 1; i < n; i++)  uf[i] = i;
}

int finduf(int u){
  return u == uf[u] ? u : uf[u] = finduf(uf[u]);
}

void unionuf(int u, int v){
  uf[finduf(u)] = finduf(v);
}

int kruskal(){
  int res = 0;

  builduf();

  sort(edges.begin(), edges.end());
  for(const pair<int, pair<int, int>> & e : edges){
    int w = e.first;
    int u = e.second.first, v = e.second.second;
    if(finduf(u) != finduf(v)){
      unionuf(u, v);
      mst[u].push_back({w, v});
      mst[v].push_back({w, u});
      res += w;
    }
  }

  return res;
}

int main(){
  cin >> n >> m;
  for(int i = 0; i < m; i++){
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    edges.push_back({w, {u, v}});
  }
  cout << "mst: " << kruskal() << '\n';
  for(int i = 0; i < n; i++){
    cout << i + 1 << ": ";
    for(const pair<int, int> &e : mst[i])  cout << "[" << e.first << ',' << e.second << "] ";
    cout << '\n';
  }
}
