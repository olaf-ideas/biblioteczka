#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n,m;
vector<int> adj[N], order;
bool vis[N];

void dfs(int u = 0){
  vis[u] = true;
  order.push_back(u);
  for(int v : adj[u])
    if(!vis[v]) dfs(v);
}

int main(){
  ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);

  cin >> n >> m;
  for(int i = 0; i < m; i++){
      int u, v;
      cin >> u >> v;
      adj[u].push_back(v);
      adj[v].push_back(u);
  }

  dfs();

  cout << "visiting order:\n";
  for(int u : order)  cout << u << " ";
  cout << "\n";
}