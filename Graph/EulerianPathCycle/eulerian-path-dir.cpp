/*
 * Desciption: Finding Eulerian Path for directed graph
 * Author: olaf_surgut
 * Complexity: O(N + M)
 * Verification: 
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 7, M = 2e6 + 7;

int n, m;
vector<int> adj[N];

vector<int> euler_path;
int cnt[N], deg[N];

void dfs(int u) {
    euler_path.push_back(u);
    while(cnt[u] < (int) adj[u].size()) {
        dfs(adj[u][cnt[u]++]);
    }
}

int find_euler_root() {
    for(int i = 0; i < n; i++) {
        for(int v : adj[i]) {
            deg[v]++;
        }
    }

    int root = -1, odd = 0;
    for(int i = 0; i < n; i++) {
        if(((int) adj[i].size() + deg[i]) & 1) {
            odd++;
            if(root == -1 || (int) adj[i].size() - deg[i] > (int) adj[root].size() - deg[root]) {
                root = i;
            }
        }
    }

    if(odd > 2) return -1;
    if(root == -1) {
        root = 0;
        while(root < n && (int)adj[root].empty())   root++;
        if(root == n)   return 0;
    }
    return root;
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v; scanf("%d %d", &u, &v);
        u--, v--;
        adj[u].push_back(v);
    }

    int root = find_euler_root();
    if(root == -1) { 
        puts("-1");
    } else {
        dfs(root);
        if((int) euler_path.size() != m + 1) {
            puts("-1");
        } else {
            for(int u : euler_path) printf("%d ", u + 1);
            puts("");
        }
    }
}
