/*
 Description: Sparse Table for RMQ problems
 Author: olaf_surgut
 Complexity: build = O(n log n), query = O(1)
 Validation: https://cses.fi/problemset/task/1647/
 */

#include <bits/stdc++.h>

using namespace std;

template <class T>
struct SparseTable {
    int n, lg;
    vector<vector<int>> table;
    vector<T> x;
    
    int argmin(int a, int b) { return x[a] < x[b] ? a : b; }

    SparseTable(vector<T> &_x) : n((int) _x.size()), lg(32 - __builtin_clz(n)), table(lg), x(_x) {
        table[0].assign(n, 0);
        iota(table[0].begin(), table[0].end(), 0);
        for(int h = 1; h < lg; h++) {
            table[h].assign(n - (1 << h) + 1, 0);
            for(int i = 0; i <= n - (1 << h); i++)
                table[h][i] = argmin(table[h - 1][i], table[h - 1][i + (1 << (h - 1))]);
        }
    }

    inline int query_index(int l, int r) {
        int h = 31 - __builtin_clz(r - l + 1);
        return argmin(table[h][l], table[h][r - (1 << h) + 1]);
    }

    inline T query(int l, int r) {
        return x[query_index(l, r)];
    }
};

int n, q;
vector<int> a;

int main() {
    scanf("%d %d", &n, &q);
    a.resize(n, 0);
    for(int i = 0; i < n; i++)  scanf("%d", &a[i]);

    SparseTable<int> table(a);

    while(q--) {
        int l, r; scanf("%d %d", &l, &r);
        l--, r--;
        printf("%d\n", table.query(l, r));
    }
}
