/*
 * Author: olaf-ideas
 * License: CC0
 * Description: Blossom algorithm for general graph matching
 * Status: tested
 * Complexity: O(n^3)
 * Link: 
 */

#include <vector>
#include <cassert>
#include <numeric>

struct GraphMatching {
	int n;
	std::vector<std::vector<int>> adj;
	std::vector<int> mat;
	std::vector<int> pre;
	std::vector<int> typ;
	std::vector<int> fat;
	std::vector<int> vis;
	int tim;
	
	GraphMatching(int _n) : n(_n), adj(n), mat(n), pre(n), typ(n), fat(n), vis(n), tim(0) { }
	
	void add_edge(int u, int v) {
		assert(0 <= u && u < n && 0 <= v && v < n);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	int get(int u) { return fat[u] == u ? u : fat[u] = get(fat[u]); }
	
	int lca(int u, int v) {
		for(++tim; ; std::swap(u, v)) if(u != -1) {
			u = get(u);
			if(vis[u] == tim)	return u;
			vis[u] = tim;
			u = (mat[u] == -1 ? -1 : pre[mat[u]]);
		}
		assert(69 == 420);
	}
	
	std::vector<int> q;
	void unite(int u, int v, int w) {
		while(get(u) != w) {
			pre[u] = v;
			if(typ[mat[u]] == 1) {
				typ[mat[u]] = 0;
				q.push_back(mat[u]);
			}
			if(get(u) == u)	fat[u] = w;
			if(get(mat[u]) == mat[u])	fat[mat[u]] = w;
			u = pre[v = mat[u]];
		}
	}
	
	int shrink(int s) {
		iota(fat.begin(), fat.end(), +0);
		fill(typ.begin(), typ.end(), -1);
		fill(pre.begin(), pre.end(), +0);
		typ[s] = 0;
		while(q.size())	q.pop_back();
		q.push_back(s);
		for(int i = 0; i < (int) q.size(); i++) {
			int u = q[i];
			for(int v : adj[u]) {
				if(!~typ[v]) {
					typ[v] = 1, pre[v] = u;
					if(mat[v] == -1) {
						while(v != -1) {
							int w = mat[pre[v]];
							mat[mat[pre[v]] = v] = pre[v];
							v = w;
						}
						return 1;
					} else {
						typ[mat[v]] = 0;
						q.push_back(mat[v]);
					}
				} else if(!typ[v] && get(u) != get(v)) {
					int w = lca(u, v);
					unite(v, u, w);
					unite(u, v, w);
				}
			}
		}
		return 0;
	}
	
	int matching() {
		fill(mat.begin(), mat.end(), -1);
		int res = 0;
		for(int i = 0; i < n; i++) if(mat[i] == -1)
			res += shrink(i);
		return res;
	}
};
