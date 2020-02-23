#include <iostream>
#include <vector>
#include <utility>
using namespace std;

const int MAXN = 100005, MAXM = 200005;

int n,m,cnt_vis[MAXN];
vector<pair<int,int>> adj[MAXN];
vector<int> euler_path;
bool done[MAXM], vis[MAXN];

int connectivity(int u){
    vis[u] = true;
	int res = 1;
	for(const pair<int,int> &v : adj[u])
		if(!vis[v.second])	
		    res += connectivity(v.second);
	return res;
}

int is_euler_path(){
	int odd_id = -1, odd_cnt = 0, 
		aliened = 0, any = 0;
	for(int i = 0; i < n; i++){
		if(adj[i].size() > 0 && adj[i].size()%2==1)
		    odd_id = i, odd_cnt++;
		else if(adj[i].size() == 0)	aliened++;
		if(adj[i].size() > 0)	any = i;
    }
	if(odd_cnt > 2 || connectivity(any)+aliened != n)
		return -1;

    if(odd_id != -1) return odd_id;
	return any;
}

void dfs(int u){
    for(;cnt_vis[u] < (int)adj[u].size(); cnt_vis[u]++){
		int edge_id = adj[u][cnt_vis[u]].first, v = adj[u][cnt_vis[u]].second;
		if(!done[edge_id]){
		    done[edge_id] = true;
			dfs(v);
		}
	}
	euler_path.push_back(u);
}

int main(){
    scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++){
		int u, v;
        scanf("%d %d", &u, &v);
		u--,v--;
		adj[u].push_back(make_pair(i,v));
		adj[v].push_back(make_pair(i,u));
	}
	int start = is_euler_path();
    if(start == -1) printf("No euler path\n");
    else{
        dfs(start);
        for(int i = 0; i < euler_path.size()-1; i++)    printf("%d - ", euler_path[i]);
        printf("\n");
    }
}