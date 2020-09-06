/*
 * Description: Bellman-Ford algorithm for shortest path from a single source vertex
 * Author: olaf_surgut
 * Complexity: O(N * M)
 * Verification: https://cses.fi/problemset/task/1673/
 */

#include <bits/stdc++.h>

using namespace std;

const long long LONG_INF = 1e18 + 7;

template<class T>
vector<long long> bellmanFord(int n, int start, vector<pair<pair<int, int>, T>> &edges) {
    vector<long long> dist(n, LONG_INF);
    dist[start] = 0;

    for(int i = 0; i < 2 * n; i++) {
        bool any = false;
        for(const pair<pair<int, int>, T> &e : edges) {
            if(dist[e.first.first] != LONG_INF && 
               dist[e.first.first] + e.second < dist[e.first.second]) {
                any |= dist[e.first.second] != -LONG_INF;
                dist[e.first.second] = max(-LONG_INF, dist[e.first.first] + e.second);
                if(i >= n - 1)  dist[e.first.second] = -LONG_INF;
            }
        }
        if(!any)    break;
    }

    return dist;
}

int n, m;
vector<pair<pair<int, int>, int>> edges;

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v, w; scanf("%d %d %d", &u, &v, &w);
        u--, v--;
        edges.push_back({{u, v}, -w});
    }

    vector<long long> dist = bellmanFord(n, 0, edges);

    if(dist[n - 1] == -LONG_INF) {
        puts("-1");
    } else {
        printf("%lld\n", -dist[n - 1]);
    }
}
