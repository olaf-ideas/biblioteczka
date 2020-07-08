#include <bits/stdc++.h>
using namespace std;

const int N = 100005, M = 200005;

int n, m, cnt[N];
vector<pair<int, int>> adj[N];
vector<int> euler_path;
bool done[M], vis[N];

int conn(int u){
  vis[u] = true;
	int res = 1;
	for(const pair<int, int> &v : adj[u])
		if(!vis[v.second])	
		    res += conn(v.second);
	return res;
}

int is_eulerian(){
  int odd_id = -1, odd_cnt = 0, aliened = 0, any = 0;
	for(int i = 0; i < n; i++){
	  if(adj[i].size() > 0 && adj[i].size() % 2 == 1)odd_id = i, odd_cnt++;
		else if(adj[i].size() == 0)	aliened++;
		if(adj[i].size() > 0)	any = i;
  }
	if(odd_cnt > 2 || conn(any) + aliened != n) return -1;
	return odd_id != -1 ? odd_id : any;
}

void dfs(int u){
    for(; cnt[u] < (int)adj[u].size(); cnt[u]++){
		int e_id = adj[u][cnt[u]].first, v = adj[u][cnt[u]].second;
		if(!done[e_id]){
		    done[e_id] = true;
			dfs(v);
		}
	}
	euler_path.push_back(u);
}

int main(){
  cin >> n >> m;
  for(int i = 0; i < m; i++){
	  int u, v;
	  cin >> u >> v;
	  u--, v--;
		adj[u].push_back({i,v});
		adj[v].push_back({i,u});
	}
	int start = is_eulerian();

	if(start != -1)	dfs(start);
	else		        euler_path.push_back(-2);

	for(int u : euler_path)	cout << u+1 << " ";
	cout << "\n";
}
