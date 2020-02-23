#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005, MAXM = 100005;

int n, m, status[MAXN], id_order[MAXN];
vector<int> adj[MAXN], order;
bool vis[MAXN];

bool check_for_cycle(){
    for(int i = 0; i < n; i++)
        if(status[i] == 0)    return false;
    return true;
}

void dfs(int u){
    vis[u] = true;
    for(int v : adj[u])
        if(!vis[v]) dfs(v);
    order.push_back(u);
}

void toposort(){
    for(int i = 0; i < n; i++)
        if(!vis[i]) dfs(i);

    reverse(order.begin(), order.end());
    for(int i = 0; i < (int)order.size(); i++)  id_order[order[i]] = i;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        u--, v--;
        status[v]++;
        adj[u].push_back(v);
    }
    if(check_for_cycle()){
        printf("Found cycle!\n");
        return 0;
    }
    printf("topoligical order: ");
    for(int u : order)  printf("%d ", u);
    printf("\n");
}   