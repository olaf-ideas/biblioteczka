// Heavy-Light Decomposition for nodes O(log ^ 2 n)
// implementation of add/sum on the path
#include <bits/stdc++.h>
#define ll long long int
using namespace std;

const int N = 100005, T = 1 << 18;

namespace seg {
  ll t[T << 1], p[T << 1];
  
  void lazy(int u, int x, int y){
    t[u] += p[u] * (y - x + 1);
    if(u < T) p[u << 1] += p[u], p[u << 1 | 1] += p[u];
    p[u] = 0;
  }
  
  void upd(int l, int r, ll v, int x=0, int y=T-1, int u=1){
    lazy(u, x, y);
    if(l > y || r < x)  return;
    if(l <= x && y <= r){
      p[u] += v;
      lazy(u, x, y);
      return;
    }
    int m = (x + y) >> 1;
    upd(l, r, v, x, m, u << 1);
    upd(l, r, v, m + 1, y, u << 1 | 1);
    t[u] = t[u << 1] + t[u << 1 | 1];
  }

  ll ask(int l, int r, int x=0, int y=T-1, int u=1){
    lazy(u, x, y);
    if(l > y || r < x)  return 0;
    if(l <= x && y <= r)  return t[u];
    int m = (x + y) >> 1;
    return ask(l, r, x, m, u << 1) + ask(l, r, m + 1, y, u << 1 | 1);
  }
}; // seg

int n, q;
vector<int> adj[N];

int sz[N], d[N], p[N], h[N], top[N], id[N], cnt = 0;

void dfs(int u){
  sz[u] = 1, h[u] = -1;
  for(int v : adj[u]) if(v != p[u]){
    d[v] = d[u] + 1, p[v] = u;
    dfs(v);
    sz[u] += sz[v];
    if(h[u] == -1 || sz[v] > sz[h[u]])  h[u] = v;
  }
}

void hld(int u, int t){
  top[u] = t, id[u] = cnt++;
  if(h[u] != -1)  hld(h[u], t);
  for(int v : adj[u]) if(v != p[u] && v != h[u]){
    hld(v, v);
  }
}

void upd(int u, int v, ll val){
  for(; top[u] != top[v]; v = p[top[v]]){
    if(d[top[u]] > d[top[v]]) swap(u, v);
    seg::upd(id[top[v]], id[v], val);
  }
  if(d[u] > d[v]) swap(u, v);
  seg::upd(id[u], id[v], val);
}

void upd(int u, ll val){
  seg::upd(id[u], id[u], val);
}

ll ask(int u, int v){
  ll res = 0;
  for(; top[u] != top[v]; v = p[top[v]]){
    if(d[top[u]] > d[top[v]]) swap(u, v);
    res += seg::ask(id[top[v]], id[v]);
  }
  if(d[u] > d[v]) swap(u, v);
  res += seg::ask(id[u], id[v]);
  return res;
}

ll ask(int u){
  return seg::ask(id[u], id[u]);
}

int main(){
  cin >> n >> q;
  for(int i = 0; i < n - 1; i++){
    int u, v; cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(0);
  hld(0, 0);
  
  while(q--){
    int t, u, v; cin >> t >> u >> v;
    u--, v--;
    if(t == 1){
      ll val; cin >> val;
      upd(u, v, val);
    }
    if(t == 2){
      cout << ask(u, v) << '\n';
    }
  }
}
