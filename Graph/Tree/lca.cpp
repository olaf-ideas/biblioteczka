#include <bits/stdc++.h>
using namespace std;

const int N = 500005, LOG = 30;

int n, q;
vector<int> adj[N];

int up[N][LOG], pre[N], post[N], cnt = 0;

void dfs(int u, int p=0){
  pre[u] = cnt++, up[u][0] = p;

  for(int i = 1; i < LOG; i++)  up[u][i] = up[up[u][i - 1]][i - 1];

  for(int v : adj[u]) if(v != p)
    dfs(v, u);

  post[u] = cnt++;
}

bool is_anc(int u, int v){
  return pre[u] < pre[v] && post[u] > post[v];
}

int lcs(int u, int v){
  if(is_anc(u, v))  return u;
  if(is_anc(v, u))  return v;

  for(int i = LOG - 1; i >= 0; i--)
    if(!is_anc(up[u][0], v))  u = up[u][i];
  return up[u][0];
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

  cin >> n;
  for(int i = 0; i < n - 1; i++){
    int u, v; cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(0);

  cin >> q;
  while(q--){
    int u, v; cin >> u >> v;
    u--, v--;
    cout << lca(u, v) + 1 << '\n';
  }
}
