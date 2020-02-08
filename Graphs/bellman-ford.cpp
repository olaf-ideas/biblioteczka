#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN = 100005, INF = (1LL<<60LL);

struct Edge{int u, v; ll w;};

int n,m,d[MAXN];
bool vis[MAXN];
vector<Edge> edges;

void bellman_ford(int s){
    fill(d,d+n,INF);
    d[s] = 0;

    for(;;){
        bool any = false;
        for(const Edge& e : edges){
            if(d[e.v] < INF && d[e.v] > d[e.u] + e.w){
                    d[e.v] = d[e.u] + e.w;
                    any = true;
            }
        }
        if(!any)    break;
    }
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++){
        int u, v;
        ll w;
        scanf("%d%d%lld", u, v, w);
        u--, v--;
        edges.push_back({u,v,w});
    }

    bellman_ford(0);

    printf("%d\n", d[n-1]);
}