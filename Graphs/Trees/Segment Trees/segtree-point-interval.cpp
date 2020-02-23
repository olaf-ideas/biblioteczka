#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 500005, TREE = (1<<19), INF = 1000000005;

struct SegTree{ // [1..n]

    ll t[TREE<<1];

    void build(vector<int>& v){
        for(int i = 1; i <= (int)v.size(); i++)
            t[i+TREE] = v[i-1];
        for(int i = TREE-1; i > 0; i--)
            t[i] = min(t[i<<1], t[i<<1|1]);
    }

    void update(int x, ll val){
        for(t[x += TREE] = val; x > 1; x >>= 1)
            t[x>>1] = min(t[x], t[x^1]);
    }

    ll query(int l, int r){ // [l,r)
        ll la = INF, ra = INF;
        for(l += TREE, r += TREE; l < r; l >>= 1, r >>= 1){
            if(l&1) la = min(la, t[l++]);
            if(r&1) ra = min(t[r--], ra);
        }
        return min(la, ra);
    }
};