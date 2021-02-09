/**
 * Author: olaf_surgut
 * License: CC0
 * Description: Mo algorithm for offline range queries with hilbert curve optimization
 * Usage: Just code insert, remove and query functions, set some ranges and run mo
 * Complexity: O(n * q^.5 * (update) + q * query)
 * Status: tested
 */

#include <algorithm>
#include <numeric>

const int Q = 1e5 + 7;

int q;

int l[Q], r[Q], id[Q];
int64_t ord[Q];

int ans[Q];

void insert(int i) {

}

void remove(int i) {

}

int query() {

}

int64_t hilbert(int x, int y) {
	const int log_q = __lg(q) + 1;

	int64_t d = 0;
	for(int s = 1 << (log_q - 1); s; s >>= 1) { 
		bool rx = x & s, ry = y & s;
		d = d << 2 | (rx * 3 ^ static_cast<int>(ry));
		if(!ry) {
			if(rx)  x = (1 << log_q) - x, y = (1 << log_q) - y;
			std::swap(x, y);
		}
	}
	return d;
}

void mo() {
	std::iota(id, id + q, 0);
	for(int i = 0; i < q; i++)
		ord[i] = hilbert(l[i], r[i]);

	std::sort(id, id + q, [&](int i, int j) {
		return ord[i] < ord[j];
	});

	int L = 0, R = -1;
	for(int i = 0; i < q; i++) {
		while(L > l[id[i]]) insert(--L);
		while(R < r[id[i]]) insert(++R);
		while(L < l[id[i]]) remove(L++);
		while(R > r[id[i]]) remove(R--);
		ans[id[i]] = query();
	}
}
