#include <bits/stdc++.h>

using namespace std;

const int T = 1 << 17;

long long tree[T << 1], lazy[T << 1];

void push(int u, int x, int y) {
    tree[u] += lazy[u] * (y - x);
    if(u < T) {
        lazy[u << 1 | 0] += lazy[u];
        lazy[u << 1 | 1] += lazy[u];
    }
    lazy[u] = 0;
}

void update(int l, int r, int val, int x = 0, int y = T, int u = 1) {
    assert(l < r && r <= T);
    push(u, x, y);
    if(l >= y || r <= x)  return;
    if(l <= x && y <= r) {
        lazy[u] += val;
        push(u, x, y);
        return;
    }
    int m = (x + y) >> 1;
    update(l, r, val, x, m, u << 1 | 0);
    update(l, r, val, m, y, u << 1 | 1);
    tree[u] = tree[u << 1 | 0] + tree[u << 1 | 1];
}

long long query(int l, int r, int x = 0, int y = T, int u = 1) {
    assert(l < r && r <= T);
    push(u, x, y);
    if(l >= y || r <= x)    return 0;
    if(l <= x && y <= r)    return tree[u];
    int m = (x + y) >> 1;
    return query(l, r, x, m, u << 1 | 0) +
           query(l, r, m, y, u << 1 | 1);
}

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int op, l, r; cin >> op >> l >> r;
        if(op == 1) {
            int v; cin >> v;
            update(l, r, v);
        } else {
            cout << query(l, r) << '\n';
        }
    }
}
