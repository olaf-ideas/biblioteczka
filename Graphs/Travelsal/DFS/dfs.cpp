#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005, MAXM = 100005;

int n,m;
vector<int> adj[MAXN], order;
bool vis[MAXN];

void dfs(int u = 0){
    vis[u] = true;
    order.push_back(u);
    for(int v : adj[u])
        if(!vis[v]) dfs(v);
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs();

    printf("visiting order: ");
    for(int u : order)  printf("%d ", u);
    printf("\n");   
}