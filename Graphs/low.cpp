#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+6;

vector<int> adj[MAXN];
int n, m, pre[MAXN], cnt = 1, low[MAXN], p[MAXN];
bool vis[MAXN];
//              { low[v] dla v != p i u-v krawedz drzewowa
// low[u] = min { pre[v] dla u-v krawedz niedrzewowa
//              { pre[u]
//
// most(u,p[u]) <=> low[u] > pre[p[u]] 
//
// punkt-arty(u) <=> (u==root && adj[u].size() > 1) || istnieje syn ze most(v,u) 
//
void dfs(int u){
    pre[u] = ++cnt, low[u] = pre[u], vis[u] = true;

    for(int v : adj[u]){
        if(v == p[u])   continue;
        if(!vis[v]) low[u] = min(low[u], pre[v]);
        else        p[v] = u, dfs(v), low[u] = min(low[u], low[v]);  
    }
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0);
    for(int u = 1; u < n; u++)
        if(low[u] > pre[p[u]]) 
            printf("most: %d - %d\n", u, p[u]);

    if(adj[0].size() > 1)   printf("punkt-arty: %d\n", 0);          

    for(int u = 1; u < n; u++)
        for(int v : adj[u])
            if(v != p[u]){
                printf("punkt-arty: %d\n", u);
                break;
            }
}