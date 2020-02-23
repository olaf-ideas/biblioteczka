#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 200005;
const ll INF = (1LL<<60LL);

int n, m;
ll d[MAXN];
vector<pair<int,ll>> adj[MAXN];

void dijkstra(int s){
    priority_queue<pair<ll,int>> pq;
    fill(d,d+n,INF);
    d[s] = 0;
    pq.push(make_pair(-d[s], s));
    while(!pq.empty()){
        int u = pq.top().second;
        ll c = pq.top().first;
        pq.pop();
        if(d[u] < c)    continue;
        for(const pair<int,ll>& e : adj[u]){
            int v = e.first;
            ll w = e.second;
            if(d[v] > d[u]+w){
                d[v] = d[u]+w;
                pq.push(make_pair(-d[v],v));
            } 
        }
    }
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++){
        int u, v;
        ll w;
        scanf("%d%d%lld", &u, &v, &w);
        u--, v--;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    dijkstra(0);
    printf("distance from 1: ");
    for(int i = 0; i < n; i++)  printf("%d: %lld ", i+1, d[i]);
    printf("\n");
}