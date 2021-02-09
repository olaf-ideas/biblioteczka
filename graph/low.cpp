/*
 * Desctiption: LOW function for bridges and articulation points in graph
 * Author: olaf-ideas
 * Complexity: O(N + M)
 * Validation: 
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 7;

struct LOW {
	int n;
	vector<vector<int>> adj;
	vector<bool> vis;
	vector<int> pre, low, p;
	int tim = 1;
	bool built = false;

	LOW(int _n) : n(_n), adj(n), vis(n), pre(n), low(n), p(n) { }

	void dfs(int u, int f = -1) {
		p[u] = f;
		vis[u] = true;
		pre[u] = low[u] = tim++;
		for(int v : adj[u]) if(v != f) {
			if(!vis[v]) {
				dfs(v, u);
				low[u] = min(low[u], low[v]);
			} else low[u] = min(low[u], pre[v]);
		}
	}

	void ae(int u, int v) {
		built = false;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void build() {
		if(built)   return;
		fill(vis.begin(), vis.end(), false);
		tim = 1;
		for(int i = 0; i < n; i++) if(!vis[i])
			dfs(i);
		built = true;
	}

	vector<pair<int, int>> find_bridges() {
		build();
		vector<pair<int, int>> res;
		for(int i = 0; i < n; i++) {
			if(p[i] != -1 && low[i] == pre[i])
				res.push_back({i, p[i]});
		}
		return res;
	}

	vector<int> find_cutpoints() {
		build();
		vector<bool> ok(n);
		for(int i = 0; i < n; i++) {
			if(p[i] != -1 && low[i] >= pre[p[i]])
				ok[p[i]] = true;
		}
		vector<int> children(n);
		for(int i = 0; i < n; i++) {
			if(p[i] != -1)
				children[p[i]]++;
		}
		for(int i = 0; i < n; i++) {
			if(p[i] == -1 && children[i] < 2)
				ok[i] = false;
		}
		vector<int> res;
		for(int i = 0; i < n; i++) if(ok[i]) {
			res.push_back(i);
		}
		return res;
	}
};
