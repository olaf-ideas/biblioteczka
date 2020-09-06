/*
 * Description: calculating LCA with Sparse table
 * Autor: olaf_surgut
 * Complexity: build = O(n log n), query = O(1)
 * Verification: https://cses.fi/problemset/task/1688/
 */


#include <bits/stdc++.h>

using namespace std;

struct Lca {
    int n, lg;
    vector<vector<int>> adj, pos;
    vector<int> start, depth;
    int cnt = 0;
    bool built = false; 
   
    Lca(int _n) : n(_n), lg(33 - __builtin_clz(n)), adj(n), pos(n << 1, vector<int>(lg)), 
                  start(n), depth(n) { }

    inline void ae(int u, int v) { adj[u].push_back(v), adj[v].push_back(u); }

    void dfs(int u, int f) {
        start[u] = cnt;
        pos[cnt++][0] = u;
        for(int v : adj[u]) if(v != f) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            pos[cnt++][0] = u;
        }
    }

    inline int get_higher(int u, int v) { return depth[u] < depth[v] ? u : v; }

    void build(int root = 0) {
        dfs(root, root);
        for(int h = 1; h < lg; h++)
            for(int i = 0; i <= cnt - (1 << h); i++)
                pos[i][h] = get_higher(pos[i][h - 1], pos[i + (1 << (h - 1))][h - 1]);
        built = true;
    }
    
    inline int rmq(int l, int r) {
        int h = 31 - __builtin_clz(r - l + 1);
        return get_higher(pos[l][h], pos[r - (1 << h) + 1][h]);
    }

    template <class T>
    int kth(int u, T k) {
        assert(0 <= u && u < n && 0 <= k && built);
        if(k > depth[u])    return -1;
        int l = start[u], r = cnt + 1;
        while(r - l > 1) {
            int m = (l + r) >> 1;
            if(depth[u] - depth[rmq(start[u], m)] <= k) l = m;
            else                                        r = m;
        }
        return rmq(start[u], l);
    }

    int query(int u, int v) {
        assert(0 <= u && u < n && 0 <= v && v < n && built);
        u = start[u], v = start[v];
        if(u > v)   swap(u, v);
        return rmq(u, v);
    }
};

int n, q;

int main() {
    scanf("%d %d", &n, &q);
    Lca lca(n);
    for(int i = 1; i < n; i++) {
        int e; scanf("%d", &e);
        e--;
        lca.ae(e, i);
    }
    lca.build();
    
    while(q--) {
        int u, k; scanf("%d %d", &u, &k);
        u--;
        int w = lca.kth(u, k);
        if(w == -1) puts("-1");
        else        printf("%d\n", w + 1);
    }

}
