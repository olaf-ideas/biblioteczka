/*
 * Description: Topological sorting algorithm for DAG
 * Author: olaf_surgut
 * Complexity: O(N + M)
 * Verification: https://cses.fi/problemset/task/1679/ https://solve.edu.pl/tasks/view/501 
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 7;

int n, m;
vector<int> adj[N];
int deg[N];

vector<int> toposort() {
    vector<int> order;

    for(int i = 0; i < n; i++) if(deg[i] == 0)
        order.push_back(i);

    for(int i = 0; i < (int) order.size(); i++)
        for(int v : adj[order[i]]) if(--deg[v] == 0)
            order.push_back(v);

    return order;
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v; scanf("%d %d", &u, &v);
        u--, v--;
        adj[u].push_back(v);
        deg[v]++;
    }
 
    vector<int> order = toposort();
    
    if((int) order.size() != n)   puts("IMPOSSIBLE");
    else {
        for(int u : order)  printf("%d ", u + 1);
        puts("");
    }

}
