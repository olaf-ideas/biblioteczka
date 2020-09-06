/*
 * Desciption: Tarjan algorithm for Strongly Connected Components
 * Author: olaf_surgut
 * Complexity: O(N + M)
 * Verification: https://cses.fi/problemset/task/1683
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 7;

int n, m;
vector<int> adj[N];

stack<int> s;
int pre[N];
int low[N], tim = 1;
int scc[N], cnt = 0;
bool vis[N];

// Note: Finding SCC are in topological order
void dfs(int u) {
    pre[u] = low[u] = tim++;
    vis[u] = true;
    s.push(u);    

    for(int v : adj[u]) {
        if(!pre[v]) dfs(v);
        if(vis[v])  low[u] = min(low[u], low[v]);
    }

    if(pre[u] == low[u]) {
        int v = -1;
        while(v != u) {
            v = s.top(); s.pop();
            vis[v] = false;
            scc[v] = cnt;
        }
        cnt++;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v; scanf("%d %d", &u, &v);
        u--, v--;
        adj[u].push_back(v);
    }

    for(int i = 0; i < n; i++)  if(!pre[i]) {
        dfs(i);
    }

    printf("%d\n", cnt);
    for(int i = 0; i < n; i++) {
        printf("%d ", scc[i] + 1);
    }
    puts("");
}
