#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

vector<int> adj[N];
int n, m, pre[N], cnt = 1, low[N], p[N];
bool vis[N];

//              { low[v] dla v != p i u-v krawedz drzewowa
// low[u] = min { pre[v] dla u-v krawedz niedrzewowa
//              { pre[u]
//
// most(u,p[u]) <=> low[u] >= pre[p[u]] 
//
// punkt-arty(u) <=> (u == root && adj[u].size() > 1) || istnieje syn ze most(v,u) 
//

void dfs(int u){
  pre[u] = low[u] = ++cnt, vis[u] = true;

  for(int v : adj[u]) if(v != p[u]){
    if(vis[v])  low[u] = min(low[v], pre[v]);
    else        p[v] = u, dfs(v), low[u] = min(low[u], low[v]);
  }
}

int main(){
  cin >> n >> m;
  for(int i = 0; i < m; i++){
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(0);
  for(int i = 1; i < n; i++)
    if(low[i] > pre[p[u]]){
      cout << "most: " << u << " - " << p[u] << '\n';
      cout << "punkt-arty: " << u << '\n';
    }

  if(adj[0].size() > 1) cout << "puntk-arty: " << 0 << '\n';
}
