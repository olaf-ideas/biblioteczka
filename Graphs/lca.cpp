#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005, LOG = 35;

int n, q;
vector<int> adj[MAXN];

int up[MAXN][LOG], pre[MAXN], post[MAXN], cnt = 0;

void dfs(int u = 0, int p = 0){
    pre[u] = cnt++;
    up[u][0] = p;
    for(int i = 1; i < LOG; i++)    up[u][i] = up[up[u][i-1]][i-1];

    for(int v : adj[u])
        if(v != p)  dfs(v, u);

    post[u] = cnt++;
}

bool is_ancestor(int u, int v){
    return pre[u] < pre[v] && post[u] > post[v];
}

int lca(int u, int v){
    if(is_ancestor(u, v))   return u;
    if(is_ancestor(v, u))   return v;

    for(int i = LOG-1; i >= 0; i--)
        if(!is_ancestor(up[u][0], v))   u = up[u][i];
    return up[u][0];
}

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    scanf("%d", &q);
    while(q--){
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%d\n", lca(u,v));
    }
}