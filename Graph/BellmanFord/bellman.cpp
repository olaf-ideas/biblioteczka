/*
 * Description: Bellman-Ford algorithm for shortest path from a single source vertex
 * Author: olaf_surgut
 * Complexity: O(N * M)
 * Verification: https://cses.fi/problemset/task/1673/
 */
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
