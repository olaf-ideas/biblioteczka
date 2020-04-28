void dfs(int u = 0){
  vis[u] = true;
  order.push_back(u);
  for(int v : adj[u])
    if(!vis[v]) dfs(v);
}