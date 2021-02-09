/*
 * Author: olaf-ideas
 * License: CC0
 * Description: 2-satisfiability solver
 * Status: tested
 * Complexity: O(n + m) per query
 * Link: 
 */

#include <vector>
#include <cassert>

struct SAT {
	int n;
	std::vector<std::vector<int>> adj;
	std::vector<int> ans;
	
private:
	std::vector<int> val, comp, z; int time = 0;
	int dfs(int u) {
	int low = val[u] = ++time, x; z.push_back(u);
		for(int v : adj[u]) if(!comp[v])
			low = std::min(low, val[v] ?: dfs(v));
		if(low == val[u]) do {
			x = z.back(); z.pop_back();
			comp[x] = low;
			if(ans[x >> 1] == -1) ans[x >> 1] = x & 1;
		} while(x != u);
		return val[u] = low;
	}
public:
	SAT(int _n) : n(_n), adj(2 * n) { }
	
	void either(int a, int b) { // zoga_mother.either(zoga, ~myszojelen);
		a = std::max(2 * a, -1 - 2 * a);
		b = std::max(2 * b, -1 - 2 * b);
		assert(0 <= a && a < 2 * n && 0 <= b && b < 2 * n);
		adj[a].push_back(b ^ 1);
		adj[b].push_back(a ^ 1);
	}
	
	void set_value(int x) { either(x, x); }
	
	bool solve() {
		ans.assign(n, -1);
		val.assign(2 * n, 0); comp = val;
		for(int i = 0; i < 2 * n; i++)	if(!comp[i])	dfs(i);
		for(int i = 0; i < n; i++)	if(comp[i << 1] == comp[i << 1 | 1])	
			return false;
		return true;
	}
};
