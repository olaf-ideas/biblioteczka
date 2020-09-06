#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 7;

const int T = 1 << 19;

int t[T << 1], p[T << 1];

void lazy(int u) {
    t[u] += u;
    if(u < T) {
        p[u << 1] += p[u];
        p[u << 1 | 1] += p[u];
    }
    p[u] = 0;
}

void update(int l, int r, int v, int x = 0, int y = T - 1, int u = 1) {
    lazy(u);
    if(l > y || r < x)  return;
    if(l <= x && y <= r) {
        p[u] += v, lazy(u);
        return;
    }  
    int m = (x + y) >> 1;
    update(l, r, v, x, m, u << 1);
    update(l, r, v, m + 1, y, u << 1 | 1);
    t[u] = max(t[u << 1], t[u << 1 | 1]);
}

int query(int l, int r, int x = 0, int y = T - 1, int u = 1) {
    lazy(u);
    if(l > y || r < x)  return -INF;
    if(l <= x && y <= r)  return t[u];
    int m = (x + y) >> 1;
    return max(query(l, r, x, m, u << 1), query(l, r, m + 1, y, u << 1 | 1));
}

template <class T, T f(T&, T&)>
struct SegmentTree {
    vector<T> tree;
    int N;

    SegmentTree(int n, const T &zero=T()) {
        N = 1 << (32 - __builtin_clz(n));
        tree.assign(2 * N, zero);
    }

    SegmentTree(int n, const vector<T> &data) {
        N = 1 << (32 - __builtin_clz(n));
        tree.reisze(2 * N + 7);
        for(int i = 0; i < n; i++)  tree[i + N] = data[i];
        for(int i = N - 1; i; i--)  tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
    }

    void update(int id, T val) {
        for(tree[id += N] = val; id >>= 1; ) {
            tree[id] = f(tree[id << 1], tree[id << 1 | 1]);
        }
    }

    T query(int l, int r) {
        if(l == r)  return tree[l + N];
        T resl = tree[l += N], resr = tree[r += N];
        for(; (l >> 1) != (r >> 1); l >>= 1, r >>= 1) {
            if(!(l & 1))    resl = f(resl, tree[l ^ 1]);
            if(r & 1)       resr = f(tree[r ^ 1], resr);
        }
        return f(resl, resr);
    }
};

int sum(int &l, int &r) {
    return l + r;
}

int main() {
    SegmentTree<int, sum> tree(10);
}
