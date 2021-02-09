#include <bits/stdc++.h>

using namespace std;

/**
 * Author: olaf_surgut
 * License: CC0
 * Description: Mo algorithm for offline range queries with hilbert curve optimization
 * Usage: Just code insert, remove and query functions, set some ranges and run mo
 * Complexity: O(n * q^.5 * (update) + q * query)
 * Status: untested
 */

#include <algorithm>
#include <numeric>

const int N = 1e5 + 7;

const int Q = 1e5 + 7;

int n, q, k, a[N];

int l[Q], r[Q], id[Q];
int64_t ord[Q];

long long ans[Q];

long long now;
int cnt[1 << 20];
void insert(int i) {
	now += cnt[a[i] ^ k];
	++cnt[a[i]];
}

void remove(int i) {
	cnt[a[i]]--;
	now -= cnt[a[i] ^ k];
}

long long query() {
	return now;
}

int64_t hilbert(int x, int y) {
	const int log_q = 20;

	int64_t d = 0;
	for(int s = 1 << (log_q - 1); s; s >>= 1) {
		bool rx = x & s, ry = y & s;
		d = d << 2 | rx * 3 ^ static_cast<int>(ry);
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

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);
	cin >> n >> q >> k;
	for(int i = 0; i < n; i++) {
		cin >> a[i + 1];
		a[i + 1] ^= a[i];
	}
	
	for(int i = 0; i < q; i++) {
		cin >> l[i] >> r[i]; l[i]--;
	}
	
	mo();
	
	for(int i = 0; i < q; i++) {
		cout << ans[i] << '\n';
	}
}
