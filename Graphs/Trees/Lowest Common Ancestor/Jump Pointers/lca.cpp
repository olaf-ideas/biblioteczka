#include <bits/stdc++.h>
using namespace std;

const int N = 200005, LOG = 35;

int n, q;
vector<int> adj[N];

int up[N][LOG], pre[N], post[N], cnt = 0;

void dfs(int u = 0, int p = 0){
  pre[u] = cnt++;
  up[u][0] = p;
  for(int i = 1; i < LOG; i++)  up[u][i] = up[up[u][i-1]][i-1];

  for(int v : adj[u]) if(v != p)  
    dfs(v, u);

  post[u] = cnt++;
}

bool is_anc(int u, int v){
  return pre[u] <= pre[v] && post[u] >= post[v];
}

int lca(int u, int v){
  if(is_anc(u, v))   return u;
  if(is_anc(v, u))   return v;

  for(int i = LOG-1; i >= 0; i--)
    if(!is_anc(up[u][0], v))  u = up[u][i];
  return up[u][0];
}

int main(){
  ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);

  cin >> n;
  for(int i = 0; i < n; i++){
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
  }
  dfs();

  cin >> q;
  while(q--){
    int u, v;
    cin >> u >> v;
    cout << lca(u,v) << "\n";
  }
}