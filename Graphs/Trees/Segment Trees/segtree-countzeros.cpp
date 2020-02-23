#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ll MAXN = (1LL<<20LL), INF = 1e18L;

ll t[2*MAXN+5],l[2*MAXN+5],m[2*MAXN];

void calc(int u){
    if(t[u<<1] + l[u<<1] < t[u<<1|1] + l[u<<1|1]){
        t[u] = t[u<<1] + l[u<<1];
        m[u] = m[u<<1];
    }
    if(t[u<<1] + l[u<<1] == t[u<<1|1] + l[u<<1|1]){
        t[u] = t[u<<1] + l[u<<1];
        m[u] = m[u<<1] + m[u<<1|1];
    }
    if(t[u<<1] + l[u<<1] > t[u<<1|1] + l[u<<1|1]){
        t[u] = t[u<<1|1] + l[u<<1|1];
        m[u] = m[u<<1|1];
    }
}

void lazy(int u){
    t[u] += l[u];
    if(u < MAXN){
        l[u<<1] += l[u];
        l[u<<1|1] += l[u];
        calc(u);
    }
    t[u] = 0;
}

void update(int a, int b, ll val, int low = 0, int high = MAXN-1, int u = 1){   //add
    lazy(u);
    if(a > high || low > b) return;
    if(a <= low && high <= b){
        l[u] += val;
        lazy(u);
        return;
    }
    int mid = (low+high)>>1;
    update(a,b,val,low,mid,u<<1);
    update(a,b,val,mid+1,high,u<<1|1);
    lazy(u);
}

ll query(){
    return MAXN-m[1];
}

void clear(){
    for(int i = MAXN; i < 2*MAXN; i++)  m[i] = 1;
    for(int i = MAXN-1; i > 0; i--)     m[i] = m[i<<1]+m[i<<1|1];
    for(int i = 0; i <= MAXN*2+5; i++)  t[i] = l[i] = 0;
}

ll q,type,a,b;

int main(){
    
}