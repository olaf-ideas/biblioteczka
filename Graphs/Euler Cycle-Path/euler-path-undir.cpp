#include <iostream>
#include <vector>
#include <utility>
using namespace std;

const int MAXN = 100005, MAXM = 200005;

int n,m,cnt[MAXN];
vector<pair<int,int>> adj[MAXN];
vector<int> euler_path;
bool done[MAXM], vis[MAXN];

int connectivity(int u){
  vis[u] = true;
	int res = 1;
  for(const auto&[id, v] : adj[u])
    if(!vis[v])
      res += connectivity(v);
  
  return res;
}

int is_euler_path(){
  int odd_id = -1, odd_cnt = 0, 
    aliened = 0, any = 0;
  for(int i = 0; i < n; i++){
    if(adj[i].size() > 0 && adj[i].size() % 2 == 1) odd_id = i, odd_cnt++;
    else if(adj[i].size() == 0)	                    aliened++;
    if(adj[i].size() > 0)	                          any = i;
  }
  if(odd_cnt > 2 || connectivity(any)+aliened != n)
    return -1;

  if(odd_id != -1) return odd_id;
    return any;
}

void dfs(int u){
  for(;cnt[u] < (int)adj[u].size(); cnt[u]++){
		int edge_id = adj[u][cnt[u]].first, v = adj[u][cnt[u]].second;
		if(!done[edge_id]){
		  done[edge_id] = true;
			dfs(v);
		}
	}
	euler_path.push_back(u);
}

int main(){
  ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);

  cin >> n >> m;
	for(int i = 0; i < m; i++){
		int u, v;
    cin >> u >> v;
		u--,v--;
		adj[u].push_back(make_pair(i,v));
		adj[v].push_back(make_pair(i,u));
	}
	int start = is_euler_path();
  if(start == -1) printf("No euler path\n");
  else{
    dfs(start);
    for(int i = 0; i < euler_path.size()-1; i++)    cout << euler_path[i] << " - ";
    cout << euler_path.back() << "\n";
  }
}