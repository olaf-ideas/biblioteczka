#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ll MAXN = (1LL<<20LL), INF = 1e18L;

struct Node{
    Node(ll x):l(max(0LL,x)),r(max(0LL,x)),b(max(0LL,x)),s(x){}
    Node():l(0),r(0),b(0),s(0){}
    static Node merge(Node &a, Node &b){
        Node r;
        r.l = max(a.l,a.s+b.l);
        r.r = max(b.r,b.s+a.r);
        r.s = a.s+b.s;
        r.b = max({a.b,b.b,a.s+b.l,b.s+a.r});
        return r;
    }
    ll l,r,b,s;
};   

struct SegTree{
    Node t[2*MAXN+5];

    void update(int x, ll val){
        for(t[x+MAXN] = Node(val); x > 1; x >>= 1) t[x>>1] = Node::merge(t[x], t[x^1]);
    }

    Node query(int l, int r){   // [l, r) !!!
        Node rl, rr;
        for(l += MAXN, r += MAXN; l < r; l >>= 1, r >>= 1){
            if(l&1) rl = Node::merge(rl, t[l++]);
            if(r&1) rr = Node::merge(t[--r],rr);
        }
        return Node::merge(rl,rr);
    }
};

SegTree tree;
int n,q;

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        ll x;
        scanf("%lld", &x);
        tree.update(i,x);
    }
    scanf("%d", &q);
    while(q--){
        char type;
        int a, b;
        scanf(" %c%d%d", &type, &a, &b);
        if(type == 'Q') printf("%lld\n", tree.query(a,b).b);
        else            tree.update(a,b);
    }
}