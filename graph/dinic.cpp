/*
 * Author: olaf-ideas
 * License: CC0
 * Description: Dinic algorithm for max flow problem
 * Status: tested
 * Complexity: O(n * m * log max capasity)
 * Link: 
 */

#include <vector>
#include <cassert>

struct Dinic {
	struct Edge {
		int u, v, c, f;
	};
	
	int n, s, t;
	std::vector<Edge> edges;
	std::vector<std::vector<int>> adj;
	
	Dinic(int _n, int _s, int _t) : n(_n), s(_s), t(_t), adj(n) { 
		assert(0 <= s && s < n && 0 <= t && t < n);
	}
	
	void add_edge(int u, int v, int capasity) {
		assert(0 <= u && u < n && 0 <= v && v < n && capasity >= 0);
		adj[u].push_back((int) edges.size());
		edges.push_back(Edge{u, v, capasity, 0});
		adj[v].push_back((int) edges.size());
		edges.push_back(Edge{v, u, 0, 0});
	}
	
	std::vector<int> d, cnt;
	bool bfs(int lim) {
		d.assign(n, -1); d[s] = 0;
		std::vector<int> q{s};
		for(int i = 0; i < (int) q.size(); i++) {
			for(int id : adj[q[i]]) {
				const Edge &e = edges[id];
				if(d[e.v] == -1 && e.c - e.f >= lim) {
					d[e.v] = d[q[i]] + 1;
					q.push_back(e.v);
				}
			}
		}
		return d[t] != -1;
	}
	
	bool dfs(int u, int lim) {
		if(u == t)	return true;
		for(int &i = cnt[u]; i < (int) adj[u].size(); i++) {
			int id = adj[u][i];
			const Edge &e = edges[id];
			if(d[e.v] == d[u] + 1 && e.c - e.f >= lim && dfs(e.v, lim)) {
				edges[id ^ 0].f += lim;
				edges[id ^ 1].f -= lim;
				return true;
			}
		}
		return false;
	}
	
	long long flow() {
		long long f = 0;
		for(int lim = 1 << 30; bfs(lim) || (lim >>= 1); ) {
			cnt.assign(n, 0);
			while(dfs(s, lim))	f += lim;
		}
		return f;
	}
	
};
