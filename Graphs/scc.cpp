#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ll MAXN = 1e6+5;

int n,m,v,u,scc[MAXN];
vector<int> adj[MAXN], adjrev[MAXN], order;
bool vis[MAXN];

void dfs(int u){
    vis[u] = true;
    for(int v : adj[u])
        if(!vis[v]) dfs(v);
    order.push_back(u);        
}

void dfs2(int u, int id){
    vis[u] = true, scc[u] = id;
    for(int v : adjrev[u])
        if(!vis[v]) dfs2(v, id);
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        u--, v--;
        adj[u].push_back(v);
        adjrev[v].push_back(u);
    }

    for(int i = 0; i < n; i++)
        if(!vis[i]) dfs(i);
    fill(vis,vis+n,false);

    for(int i = n-1, id = 0; i >= 0; i--)
        if(!vis[order[i]])  dfs2(order[i], id), id++;

    printf("scc:\n");
    for(int i = 0; i < n; i++)
        printf("%d: %d\n", i, scc[i]);
}