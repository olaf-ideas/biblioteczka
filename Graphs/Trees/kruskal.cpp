// Kruskal Algorithm O(m log m + m log m)

#include <bits/stdc++.h>
using namespace std;

const int N = 500005;

int n, m, uf[N];
vector<pair<int,pair<int,int>>> edges;
vector<pair<int,int>> mst[N];

void build_uf(){for(int i=1;i<n;i++)uf[i]=i;}
int find_uf(int u){return uf[u]==u?u:uf[u]=find_uf(uf[u]);}
void union_uf(int u, int v){(rand()&1)?uf[find_uf(u)]=uf[find_uf(v)]:uf[find_uf(v)]=uf[find_uf(u)];}

int kruskal(){
  int ans = 0;
  build_uf();
  
  sort(edges.begin(), edges.end());
  
  for(const auto& [w, e] : edges){
    auto [u, v] = e;
    if(find_uf(u) != find_uf(v)){
      union_uf(u, v);
      mst[u].push_back({w, v});
      mst[v].push_back({w, u});
      ans += w;
    }
  }
  return ans;
}

int main(){
  ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);
  
  cin >> n >> m;
  for(int i = 0; i < m; i++){
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    edges.push_back(make_pair(w, make_pair(u,v)));
  }
  cout << "mst: " << kruskal() << "\n";
  for(int i = 0; i < n; i++){
    cout << i+1 << ": ";
    for(const auto&[u, v] : mst[i])    cout << "[ " << u << ", " << v << "], ";
    cout << "\n";
  }
}