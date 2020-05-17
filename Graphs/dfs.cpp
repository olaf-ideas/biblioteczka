// aha (nie nie nie nie debugowane)
void dfs(int u = 0){
  vis[u] = true;
  for(int v : adj[u])
    if(!vis[v]) dfs(v);
}