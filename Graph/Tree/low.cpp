#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

vector<int> adj[N];
int n, m, pre[N], cnt = 1, low[N], p[N];
bool vis[N];

//              { low[v] dla v != p i (u, v) krawedz drzewowa
// low[u] = min { pre[v] dla v != p i (u, v) krawedz niedrzewowa
//              { pre[u]
//
// most(u,p[u]) <=> low[u] > pre[p[u]] 
//
// punkt-arty(u) <=> (u == root && krawedzie drzewowe > 1) || (most(u, p[u]) && nie lisc() 
//

void dfs(int u){
  pre[u] = low[u] = cnt++;
  vis[u] = true;

  for(int v : adj[u]) if(v != p[u]){
    if(vis[v])  low[u] = min(low[v], pre[v]);
    else        p[v] = u, dfs(v), low[u] = min(low[u], low[v]);
  }
}

bool most(int u){return low[u] > pre[p[u]];}

bool punkt_arty(int u){
  if(u == 0){
    int c = 0;
    for(int v : adj[u]) if(p[v] == u) c++;
    return c > 1;
  }
  return most(u) && (int)adj[u].size() > 1;
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
 
  cout << "low: ";
  for(int i = 0; i < n; i++)  cout << low[i] << ' ';
  cout << '\n';

  for(int i = 1; i < n; i++){
    if(most(i)) cout << "most: " << i + 1 << " - " << p[i] + 1 << '\n';
  }

  for(int i = 0; i < n; i++){
    if(punkt_arty(i)) cout << "punkt-arty: " << i + 1 << '\n';
  }
}
