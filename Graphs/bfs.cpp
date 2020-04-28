void bfs(int s = 0){
   vector<int> q;
   vis[s] = true;
   q.push_back(s);
   for(int i = 0; i < (int)q.size(); i++){
     for(int v : adj[q[i]]){
       vis[v] = true;
       q.push_back(v);
     }
   }
}