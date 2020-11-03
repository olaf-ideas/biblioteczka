#include <bits/stdc++.h>

using namespace std;

struct SegmentTree {
    struct Node {
        ... a = ...;
        void apply(int l, int r, ... v) {
            ...
        }        
    };

    Node unite(const Node &a, const Node &b) const {
        Node res;
        ...
        return res;
    }

    inline void push(int u, int l, int r) {
        int m = (l + r) >> 1;
        int v1 = u + 1, v2 = u + ((m - l + 1) << 1);
        ...
        if(tree[u].add != 0) {
            tree[v1].apply(l, m, tree[u].add);
            tree[v2].apply(m + 1, r, tree[u].add);
            tree[u].add = 0;
        }
    }

    int n;
    vector<Node> tree;

    void build(int x, int l, int r) {
        if(l == r)  return;
        int m = (l + r) >> 1;
        int v1 = x + 1, v2 = u + ((m - l + 1) << 1);
        build(v1, l, m);
        build(v2, m + 1, r);
        tree[u] = unite(tree[v1], tree[v2]);
    }

    Node query(int l, int r, int x, int y, int u) {
        if(l <= x && y <= r)    return tree[u];
        int m = (x + y) >> 1;
        int v1 = u + 1, v2 = u + ((m - l + 1) << 1);
        push(u, l, r);
        node res{};
        if(y <= m) {
            res = query(l, r, x, m, v1);
        } else {
            if(x > m) {
                res = query(l, r, m + 1, y, v2);
            } else {
                res = unite(query(l, r, x, m, v1), query(l, r, m + 1, y, v2));
            }
        }
        tree[u] = unite(tree[v1], tree[v2]);
        return res;
    }

    template <typename ... M>
    void update(int l, int r, int x, int y, int u, const M&... v) {
        if(l <= x && y <= r) {
            tree[u].apply(v);
            return;
        }
        int m = (x + y) >> 1;
        int v1 = u + 1, v2 = u + ((m - l + 1) << 1);
        push(u, l, r);
        if(y <= m) {
            update(l, r, x, m, v1, v);
        }
        if(x > m) {
            update(l, r, m + 1, y, v2, v);
        }
        tree[u] = unite(tree[v1], tree[v2]);
    }

    SegmentTree(int _n) : n(_n) {
        assert(n > 0);
        tree.resize(2 * n - 1);
        build(0, 0, n - 1);
    }
    
    Node query(int l, int r) {
        assert(0 <= l && l <= r && r <= n - 1);
        return query(l, r, 0, n - 1, 0);
    }

    Node query(int p) {
        assert(0 <= p && p <= n - 1);
        return query(p, p, 0, n - 1, 0);
    }

    template <typename... M>
    void update(int l, int r, const M&... v) {
        assert(0 <= l && l <= r && r <= n - 1);
        update(l, r, 0, n - 1, 0, v);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
