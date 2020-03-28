#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = (1LL<<60LL);

struct segtree{
    vector<ll> t, p;
    int base = 1;
    segtree(vector<ll> x){
        while(base < (int)x.size()) base <<= 1;
        t.resize(2*base, 0), p.resize(2*base, 0);
        for(int i = 0; i < (int)x.size(); i++)  t[i+base] = x[i];
        for(int i = base-1; i > 0; i--)         t[i] = max(t[i<<1], t[i<<1|1]);
    }
    void lazy(int u){
        t[u] += p[u];
        if(u < base)    p[u<<1] += p[u], p[u<<1|1] += p[u];
        p[u] = 0;
    }
    void upd(int l, int r, ll v, int x = 0, int y = -1, int u = 1){
        lazy(u);
        if(y == -1) y = base-1;
        if(l > y || r < x)  return;
        if(l <= x && y <= r){
            p[u] += v;
            lazy(u);
            return;
        }
        int m = (x+y)>>1;
        upd(l,r,v,x,m,u<<1),upd(l,r,v,m+1,y,u<<1|1);
        t[u] = max(t[u<<1], t[u<<1|1]);
    }
    ll ask(int l, int r, int x = 0, int y = -1, int u = 1){
        lazy(u);
        if(y == -1) y = base-1;
        if(l > y || r < x)  return -INF;
        if(l <= x && y <= r)    return t[u];
        int m = (x+y)>>1;
        return max(ask(l,r,x,m,u<<1), ask(l,r,m+1,y,u<<1|1));
    }
};

int n, q, t, l, r;
ll v;
vector<ll> a;

int main(){
    cin >> n;
    a.resize(n);
    for(int i = 0; i < n; i++)  cin >> a[i];
    segtree sg(a);
    cin >> q;
    while(q--){
        cin >> t >> l >> r;
        if(t == 1){
            cin >> v;
            sg.upd(l,r,v);
        }else   cout << sg.ask(l,r) << "\n";
    }
}