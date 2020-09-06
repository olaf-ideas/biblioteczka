/*
 * Desciption: Finding Eulerian Path for undirected graph
 * Author: olaf_surgut
 * Complexity: O(N + M)
 * Verification: https://solve.edu.pl/contests/download_desc/3095
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7, M = 2e5 + 7;

int n, m;
vector<pair<int, int>> adj[N]; // <neighbour, edge_id>

vector<int> euler_path;
int cnt[N], done[M];

void dfs(int u) {
    while(cnt[u] < (int) adj[u].size()) {
        int v    = adj[u][cnt[u]].first;
        int e_id = adj[u][cnt[u]].second;
        cnt[u]++;
        if(done[e_id]++ == 0)   dfs(v);
    }
    euler_path.push_back(u);
}

int find_euler_root() {
    int root = -1, odd = 0;
    for(int i = 0; i < n; i++) {
        if((int) adj[i].size() & 1) {
            odd++;
            root = i;
        }
    }
    if(odd > 2) return -1;
    if(root == -1) {
        root = 0;
        while(root < n && (int) adj[root].empty())  root++;
        if(root == n)   return 0;
    }
    return root;
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v; scanf("%d %d", &u, &v);
        u--, v--;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    int root = find_euler_root();
    if(root == -1) { 
        puts("-1"); // not proper graph
    } else {
        dfs(root);
        if((int) euler_path.size() != m + 1) puts("-1"); // edges not connected
        else {
            for(int u : euler_path) printf("%d ", u + 1);
            puts("");
        }
    }
}
