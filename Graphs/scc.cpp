// przyda sie na nastepnego OI i 5 kolejnych
#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, m, group[N];
vector<int> adj[N], adjrev[N], order;
bool vis[N];

void dfs(int u){
  vis[u] = true;
  for(int v : adj[u])
    if(!vis[v]) dfs(v);
  order.push_back(u);        
}

void dfs2(int u, int id){
  vis[u] = true, group[u] = id;
  for(int v : adjrev[u])
    if(!vis[v]) dfs2(v, id);
}

void scc(){
  for(int i = 0; i < n; i++)
    if(!vis[i]) dfs(i);
  fill(vis, vis+n, false);

  for(int i = n-1, id = 0; i >= 0; i--)
    if(!vis[order[i]])  dfs2(order[i], id), id++;
}

int main(){
  ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);

  cin >> n >> m;
  for(int i = 0; i < m; i++){
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adjrev[v].push_back(u);
  }

  cout << "scc:\n";
  for(int i = 0; i < n; i++)
    cout << i << ": " << group[i] << "\n";
}