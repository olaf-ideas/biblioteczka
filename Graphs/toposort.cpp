#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, m, status[N], id_order[N];
vector<int> adj[N], order;
bool vis[N];

bool check_for_cycle(){
  for(int i = 0; i < n; i++)
    if(status[i] == 0)    return false;
  return true;
}

void dfs(int u){
  vis[u] = true;
  for(int v : adj[u])
    if(!vis[v]) dfs(v);
  order.push_back(u);
}

void toposort(){
  for(int i = 0; i < n; i++)
    if(!vis[i]) dfs(i);

  reverse(order.begin(), order.end());
  for(int i = 0; i < (int)order.size(); i++)  id_order[order[i]] = i;
}

int main(){
  ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);

  cin >> n >> m;
  for(int i = 0; i < m; i++){
    int u, v;
    cin >> u >> v;
    u--, v--;
    status[v]++;
    adj[u].push_back(v);
  }
  if(check_for_cycle()){
    cout << "Found cycle!\n";
    return 0;
  }
  cout << "Topological order: ";
  for(int u : order)  cout << u << " ";
  cout << "\n";
}   