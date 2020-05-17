// nie tykać, eksponat (nie debugowane)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN = 200005, INF = (1LL<<60LL);

struct SegTree{
    ll t[MAXN], l[MAXN];
    void lazy(int u){
        t[u] += l[u];
        if(u < MAXN)    l[u<<1] += l[u], l[u<<1|1] += l[u];
        l[u] = 0;
    }
    
    void build(vector<ll>& v){
        fill(t,t+MAXN, INF);
        for(int i = 0; i < (int)v.size(); i++)  t[i+MAXN] = v[i];
        for(int i = MAXN-1; i > 0; i >>= 1)     t[i] = min(t[i<<1], t[i<<1|1]);
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
        if(a > high || b < low) return;
        if(a <= low && high <= b)   return t[u];
        int mid = (low+high)>>1;
        return min(query(a,b,low,mid,u<<1), query(a,b,mid+1,high,u<<1|1));
    }

    void update(int x, ll val){update(x,x,val);}
    ll query(int x){return query(x,x);}
};

SegTree tree;
int n, q;
vector<ll> v;

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        v.emplace_back();
        scanf("%lld", &v.back());
    }
    tree.build(v);

    scanf("%d", &q);
    while(q--){
        int type;
        scanf("%d", &type);
        int a, b, x;
        ll val;
        switch(type){
            case 0:
                scanf("%d%d", &a, &b);
                printf("%lld\n", tree.query(a,b));
                break;
            case 1:
                scanf("%d", &x);
                printf("%lld\n", tree.query(x));
                break;
            case 2:
                scanf("%d%d%lld", &a, &b, &val);
                tree.update(a,b,val);
                break;
            case 3:
                scanf("%d%lld", &x, &val);
                tree.update(x,val);
                break;
        }
    }
}