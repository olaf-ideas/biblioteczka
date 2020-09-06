/*
 * Description: Dijkstra algorithm for shortest path from a single source vertex
 * Author: olaf_surgut
 * Complexity: O(N log M)
 * Verification: https://cses.fi/problemset/task/1671/ 
 */

#include <bits/stdc++.h>

using namespace std;

const long long LONG_INF = 1e18 + 7;

template<class T>
vector<long long> dijkstra(int start, vector<vector<pair<int, T>>> adj) {
    vector<long long> dist(adj.size(), LONG_INF);
    dist[start] = 0;

    priority_queue<pair<long long, int>> q;
    q.push({-dist[start], start});

    while(q.size()) {
        int u = q.top().second;
        long long d = q.top().first;
        q.pop();
        if(-dist[u] != d)    continue;
    
        for(const pair<int, T> &e : adj[u]) {
            int v = e.first;
            if(dist[v] > dist[u] + e.second) {
                dist[v] = dist[u] + e.second;
                q.push({-dist[v], v});
            }
        }
    }

    return dist;
}

int n, m;
vector<vector<pair<int, int>>> adj;

int main() {
    scanf("%d %d", &n, &m);
    adj.resize(n);
    for(int i = 0; i < m; i++) {
        int u, v, w; scanf("%d %d %d", &u, &v, &w);
        u--, v--;
        adj[u].push_back({v, w});
    }

    vector<long long> dist = dijkstra(0, adj);

    for(int i = 0; i < n; i++) {
        printf("%lld ", dist[i]);
    }
    puts("");
}
