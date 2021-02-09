/*
 * Author: olaf-ideas
 * License: CC0
 * Description: tourist-like segment tree implementation
 * Status: untested
 * Complexity: O(n) build / O(log n) query
 * Link: 
 */

#include <vector>
#include <cassert>

struct SegmentTree {
	struct Node {
		// ... a = ...;
		void apply(int l, int r, ... v) {
			// ...
		}
	};
	
	Node unite(const Node &a, const Node &b) const {
		Node res;
		
		return res;
	}
	
	void push(int u, int x, int y) {
		int m = (x + y) >> 1;
		int z = u + ((m - x + 1) << 1);
		
	}
	
	int n;
	std::vector<Node> tree;
	
	SegmentTree(int _n) : n(_n), tree(2 * n) { }
	
	Node query(int l, int r, int x, int y, int u) {
		if(l <= x && y <= r)	return  tree[u];
		int m = (x + y) >> 1;
		int z = u + ((m - x + 1) << 1);
		push(u, x, y);
		Node res{};
		if(r <= m)		res = query(l, r, x, m, u + 1);
		else if(l > m)	res = query(l, r, m + 1, y, z);
		else 			res = unite(query(l, r, x, m, u + 1),
									query(l, r, m + 1, y, z));
		tree[u] = unite(tree[u + 1], tree[z]);
		return res;
	}
	
	template <typename... M>
	void update(int l, int r, int x, int y, int u, const M&... v) {
		if(l <= x && y <= r)	return void(tree[x].apply(l, r, v...));
		int m = (x + y) >> 1;
		int z = u + ((m - x + 1) << 1);
		push(u, x, y);
		if(l <= m)	update(l, r, x, m, u + 1, v...);
		if(r > m)	update(l, r, m + 1, y, z, v...);
		tree[u] = unite(tree[u + 1], tree[z]);
	}
	
	Node query(int l, int r) {
		assert(0 <= l && l <= r && r <= n - 1);
		return query(l, r, 0, n - 1, 0);
	}
	
	Node query(int p) {
		assert(0 <= p && p <= n - 1);
		return query(p, p, 0, n - 1, 0);
	}
	
	template <typename... M>
	void update(int l, int r, const M&... v) {
		assert(0 <= l && l <= r && r <= n - 1);
		update(l, r, 0, n - 1, 0, v...);
	}
};
