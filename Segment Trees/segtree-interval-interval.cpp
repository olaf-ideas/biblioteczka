#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ll MAXN = (1LL<<20LL), INF = 1e18L;

struct SegTree{
    SegTree(int _base){
        while(base < _base) base <<= 1;
        t.resize(base*2+5,0),l.resize(base*2+5,0);
    }

    int base = 1;
    vector<ll> t,l;
    unordered_set<int> nodes;
    int best;

    void lazy(int u){
        t[u] += l[u];
        if(u < base)    l[u<<1] += l[u], l[u<<1|1] += l[u];
        l[u] = 0;
    }

    void update(int a, int b, ll val, int low = 0, int high = -1, int u = 1){
        lazy(u);
        if(high == -1)  high = base-1;
        if(a > high || b < low) return;
        if(a <= low && high <= b){
            l[u] += val;
            lazy(u);
            return;
        }
        int mid = (low+high)>>1;
        update(a,b,val,low,mid,u<<1), update(a,b,val,mid+1,high,u<<1|1);
    }

    ll query(int a, int b, int low = 0, int high = -1, int u = 1){
        lazy(u);
        if(high == -1)  high = base-1;
        if(a > high || b < low)     return -INF;
        if(a <= low && high <= b)   return t[u];
        int mid = (low+high)>>1;
        return max(query(a,b,low,mid,u<<1), query(a,b,mid+1,high,u<<1|1));
    }
};

int n, q;

int main(){
    cin >> n >> q;
    SegTree tree(n);
    while(q--){
        int t;
        cin >> t;
        if(t == 0){
            int a, b;
            ll val;
            cin >> a >> b >> val;
            tree.update(a,b,val);
        }else{
            int a,b;
            cin >> a >> b;
            cout << tree.query(a,b) << "\n";
        }
    }    
}