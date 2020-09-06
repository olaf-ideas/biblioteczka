/*
 * Desctiption: Kruskal algorithm for Minimal Spanning Tree
 * Author: olaf_surgut
 * Complexity: O(M log M + M log* M)
 * Validation: https://solve.edu.pl/tasks/view/495
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 2e6 + 7;

int uf[N], sz[N];

int Find(int u) { return u == uf[u] ? u : uf[u] = Find(uf[u]); }
bool Union(int u, int v) {
    u = Find(u), v = Find(v);
    if(u == v)  return false;
    if(sz[u] > sz[v])   swap(u, v);
    uf[u] = v;
    sz[v] += sz[u];
    return true;
}
void Build(int n) {
    iota(uf, uf + n, 0);
    fill(sz, sz + n, 1);
}

vector<int> mst(vector<pair<pair<int, int>, int>> &edges) {
    vector<int> id(edges.size());
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](int a, int b) {
        return edges[a].second < edges[b].second;
    });
    
    Build((int) edges.size());
    vector<int> res;
    for(int i : id) {
        if(Union(edges[i].first.first, edges[i].first.second)) {
            res.push_back(i);
        }
    }
    return res;
}

int n, m;
vector<pair<pair<int, int>, int>> edges;

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v, w; scanf("%d %d %d", &u, &v, &w);
        u--, v--;
        edges.push_back({{u, v}, w});
    }
    vector<int> id = mst(edges);
    long long ans = 0;
    for(int i : id) ans += edges[i].second;
    printf("%lld\n", ans); 
}
