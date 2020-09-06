#include <bits/stdc++.h>

using namespace std;

typedef long long int LL;

const int INF = 1e9 + 7;

const int N = 1e5 + 7;

struct SegmentTree {
    vector<int> tree;
    int T;
    SegmentTree(int n) {
        T = 1 << (32 - __builtin_clz(n));
        tree.assign(T << 1, 0);
    }

    void update(int id, int val) {
        for(tree[id += T] = val; id >>= 1; )
            tree[id] = tree[id << 1] + tree[id << 1 | 1];
    }

    int query(int l, int r, int x, int y, int u) {
        if(l > y || r < x)  return 0;
        if(l <= x && y <= r)    return tree[u];
        int m = (x + y) >> 1;
        return query(l, r, x, m, u << 1) + query(l, r, m + 1, y, u << 1 | 1);  
    }

    int query(int l, int r) { return query(l, r, 0, T - 1, 1); }
};

template <bool EDGES>
struct HLD {
    int n, tt=0;
    SegmentTree tree;
    
    vector<vector<int>> adj;
    vector<pair<pair<int, int>, int>> edges;

    vector<int> p, sz, d, id, h, idr;

    HLD(int _n) 
        : n(_n), tree(n), adj(n, vector<int>()), p(n, -1), sz(n), d(n), id(n), h(n), idr(n) { }

    void ae(int u, int v, int c) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({{u, v}, c});
    }

    void build(int root=0) { 
        assert((int)edges.size() == n - 1);
        dfs(root); hld(root); 
    }

    void dfs(int u) {
        sz[u] = 1;
        for(int &v : adj[u]) if(v != p[u]) {
            p[v] = u, d[v] = d[u] + 1;
            dfs(v);
            sz[u] += sz[v];
            if(sz[v] > sz[adj[u][0]])   swap(adj[u][0], v);
        }
    }

    void hld(int u) {
        id[u] = tt++;
        idr[id[u]] = u;
        for(int v : adj[u]) if(v != p[u]) {
            h[v] = (v == adj[u][0] ? h[u] : v);
            hld(v);
        }
    }

    template <class B> void process(int u, int v, B op) {
        for(; h[u] != h[v]; v = p[h[v]]) {
            if(d[h[u]] > d[h[v]])   swap(u, v);
            op(id[h[v]], id[v]);
        }
        if(d[u] > d[v]) swap(u, v);
        op(id[u] + EDGES, id[v]);
    }
};
