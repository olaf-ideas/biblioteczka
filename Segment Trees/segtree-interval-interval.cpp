#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ll MAXN = (1LL<<20LL), INF = 1e18L;

struct SegTree{
    ll t[2*MAXN], l[2*MAXN];

    void build(vector<ll> &v){
        fill(t,t+2*MAXN,INF);
        for(int i = 0; i < (int)v.size(); i++)  t[i+MAXN] = v[i];
        for(int i = MAXN-1; i > 0; i--)         t[i] = min(t[i<<1], t[i<<1|1]);
    }

    void lazy(int u){
        t[u] += l[u];
        if(u < MAXN)    l[u<<1] += l[u], l[u<<1|1] += l[u];
        l[u] = 0;
    }

    void update(int a, int b, ll val, int low = 0, int high = MAXN-1, int u = 1){
        lazy(u);
        if(a > high || b < low) return;
        if(a <= low && high <= b){
            l[u] += val;
            lazy(u);
            return;
        }
        int mid = (low+high)>>1;
        update(a,b,val,low,mid,u<<1);
        update(a,b,val,mid+1,high,u<<1|1);
    }

    ll query(int a, int b, int low = 0, int high = MAXN-1, int u = 1){
        lazy(u);
        if(a > high || b < low)     return INF;
        if(a <= low && high <= b)   return t[u];
        int mid = (low+high)>>1;
        return min(query(a,b,low,mid,u<<1), query(a,b,mid+1,high,u<<1|1));
    }
};

SegTree tree;
int n,q,l,r;
vector<ll> a;

int main(){
    scanf("%d", &n);
    a.resize(n);
    for(int i = 0; i < n; i++)  scanf("%lld", &a[i]);
    tree.build(a);

    scanf("%d", &q);
    while(q--){
        scanf("%d%d", &l, &r);
        printf("%lld\n", tree.query(l,r));
    }
}