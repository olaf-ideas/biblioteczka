#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 200005;
const ll INF = (1LL<<60LL);

int n, m;
vector<pair<int,ll>> adj[N];
ll d[N];

vector<int> dijkstra(int s){
  fill(d, d+n, INF);

  priority_queue<pair<ll,int>> q;
  q.push({0,s});
  while(!q.empty()){
    auto[c, u] = q.top();
    q.pop();
    if(c != d[u])   continue;
    for(const auto&[v, w] : adj[u]){
      if(d[v] > d[u] + w){
        d[v] = d[u] + w;
        q.push({d[v], v});
      }
    }
  }
}

int main(){
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for(int i = 0; i < m; i++){
    int u, v;
    ll w;
    cin >> u >> v >> w;
    u--, v--;
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
  }
  dijkstra(0);
  cout << "distance from 1:\n";
  for(int i = 0; i < n; i++)  cout << i+1 << ": " << d[i] << "\n";
}