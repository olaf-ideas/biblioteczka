 // tak, musiałem mieć to w biblioteczce
void bfs(int s=0){
   vector<int> q={s};
   vis[s] = true;
   for(int i = 0; i < (int)q.size(); i++){
     for(int v : adj[q[i]]){
       vis[v] = true;
       q.push_back(v);
     }
   }
}
