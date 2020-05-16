#include <bits/stdc++.h>
using namespace std;

const int MAXN = (1<<18), INF = 1000000005;

int t[2*MAXN], p[2*MAXN];

void build(){
    for(int i = MAXN-1; i > 0; i >>= 1) t[i] = min(t[i<<1], t[i<<1|1]);
}

void lazy(int u){
    t[u] += p[u];
    if(u < MAXN)    p[u<<1] += p[u], p[u<<1|1] += p[u];
    p[u] = 0;
}

void upd(int l, int r, int v, int x = 0, int y = MAXN-1, int u = 1){
    lazy(u);
    if(l > y || r < x) return;
    if(l <= x && y <= r){
        p[u] += v;
        lazy(u);
        return;
    }
    int m = (x+y)>>1;
    upd(l,r,v,x,m,u<<1), upd(l,r,v,m+1,y,u<<1|1);
}

int ask(int l, int r, int x = 0, int y = MAXN-1, int u = 1){
    lazy(u);
    if(l > y || r < x)      return INF;
    if(l <= x && y <= r)    return t[u];
    int m = (x+y)>>1;
    return min(ask(l,r,x,m,u<<1), ask(l,r,m+1,y,u<<1|1));
}

int main(){

}
