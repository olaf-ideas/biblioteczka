#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005, MAXM = 100005;

int n, m;
vector<int> adj[MAXN], order;
bool vis[MAXN];

void bfs(int beg = 0){
    queue<int> q;
    vis[beg] = true;
    q.push(beg);
    order.push_back(beg);

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : adj[u]){
            if(!vis[v]){
                vis[v] = true;
                q.push(v);
                order.push_back(v);
            }
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bfs();

    printf("visiting order: ");
    for(int u : order)  printf("%d ", u);
    printf("\n");    
}