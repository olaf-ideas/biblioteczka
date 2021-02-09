#include <vector>
#include <cassert>
#include <numeric>

struct BipartieMatching {
	int n, m;
	std::vector<std::vector<int>> adj;
	std::vector<int> l;
	std::vector<int> r;
	std::vector<bool> vis;
	
	BipartieMatching(int _n, int _m) : n(_n), m(_m), adj(n), l(n, -1), r(m, -1), vis(n) { }
	
	void add_edge(int u, int v) {
		assert(0 <= u && u <= n - 1 && 0 <= v && v <= m - 1);
		adj[u].push_back(v);
	}
	
	int dfs(int u) {
		if(vis[u])	return false;
		vis[u] = true;
		
		for(int v : adj[u]) if(r[v] == -1)
			return l[u] = v, r[v] = u, true;
		for(int v : adj[u]) if(dfs(r[v]))
			return l[u] = v, r[v] = u, true;
		return false;
	}
	
	int matching() {
		int ok = true;
		while(ok--) {
			fill(vis.begin(), vis.end(), false);
			for(int i = 0; i < n; i++) if(l[i] == -1)
				ok |= dfs(i);
		}
		int res = 0;
		for(int i = 0; i < n; i++)
			res += (l[i] != -1);
		return res;
	}
};
