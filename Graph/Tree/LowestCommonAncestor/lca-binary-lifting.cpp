/*
 * Desciption: calculating LCA with binary lifting technique
 * Author: olaf_surgut
 * Compexity: build = O(n log n), query = O(log n)
 * Validation: https://www.spoj.com/problems/LCA/ https://cses.fi/problemset/task/1688/
 */

#include <bits/stdc++.h>

using namespace std;

struct Lca {
    int n, lg;
    vector<vector<int>> adj, p;
    vector<int> pre, pos;
    int tim = 0;
    bool built = false;    

    Lca(int _n) : n(_n), lg(32 - __builtin_clz(n)), adj(n), p(n, vector<int>(lg)), pre(n), pos(n) { } 

    inline void ae(int u, int v) { adj[u].push_back(v), adj[v].push_back(u); }

    void dfs(int u, int f) {
        p[u][0] = f;
        pre[u] = tim++;
        for(int i = 1; i < lg; i++) {
            if(p[u][i - 1] != -1)   p[u][i] = p[p[u][i - 1]][i - 1];
            else                    p[u][i] = -1;
        }
        for(int v : adj[u]) if(v != f) {
            dfs(v, u);
        }
        pos[u] = tim++;
    }

    void build(int root = 0) {
        tim = 0;
        dfs(root, -1);
        built = true;
    }

    inline bool is_anc(int u, int v) { return pre[u] <= pre[v] && pos[u] >= pre[v]; }

    template <class T>
    int kth(int u, T k) {
        assert(built && 0 <= u && u < n && 0 <= k);
        if(k >= (1 << lg))  return -1;
        for(int i = 0; i < lg && u != -1; i++) if(k & (1 << i))
            u = p[u][i];
        return u;
    }

    int query(int u, int v) {
        assert(built && 0 <= u && u < n && 0 <= v && v <= n);
        if(is_anc(u, v))    return u;
        if(is_anc(v, u))    return v;

        for(int i = lg - 1; i >= 0; i--)
            if(!is_anc(p[u][i], v)) u = p[u][i];
        return p[u][0];
    }
};

int n, q;

int main() {
    scanf("%d %d", &n, &q);
    Lca lca(n);
    for(int i = 1; i < n; i++) {
        int e; scanf("%d", &e);
        e--;
        lca.ae(i, e);
    }
    lca.build();

    while(q--) {
        int u, v; scanf("%d %d", &u, &v);
        u--;
        int w = lca.kth(u, v);
        if(w == -1) puts("-1");
        else        printf("%d\n", w + 1);
    }
}
