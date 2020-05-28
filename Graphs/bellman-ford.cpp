#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100005;
const ll INF = 1LL<<60LL;

struct Edge{int u, v; ll w;};

int n, m;
vector<Edge> edges;
ll d[MAXN];
bool vis[MAXN];

void bellman_ford(int s = 0){
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
  ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);

  cin >> n >> m;
  for(int i = 0; i < m; i++){
      int u, v;
      ll w;
      cin >> u >> v >> w;
      u--, v--;
      edges.push_back({u,v,w});
  }

  bellman_ford();
  
  cout << "distance from 1:\n";
  for(int i = 0; i < n; i++){
      if(d[i] == INF) cout << i+1 << ": inf" << "\n";
      else            cout << i+1 << ": " << d[i] << "\n";
  }
  cout << "\n";
}
