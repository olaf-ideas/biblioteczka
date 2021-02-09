/**
 * Author: olaf-ideas
 * License: CC0
 * Description: Hasing string and binsearch technique
 * Complexity: O(|s|) build, O(|1|) query, O(log min |s|, |t|) compare
 * Status: tested
 */

#include "../math/modulo.h"

#include <vector>
#include <string>

inline int to_int(char s) {
	if('0' <= s && s <= '9')    return s - '0' + 1;
	if('a' <= s && s <= 'z')    return s - 'a' + 11;
	return s - 'A' + 37;
}

template <int mod, int base>
struct SlowHash {
	int n; std::vector<int> p, h;
	SlowHash(const std::string &s) : n((int) s.size()), p(n, 1), h(n, n ? to_int(s[0]) : 0) {
		for(int i = 1; i < n; i++)  p[i] = mul(p[i - 1], base, mod);
		for(int i = 1; i < n; i++)  h[i] = add(mul(h[i - 1], base, mod), to_int(s[i]), mod);
	}
	int get(int l, int r) const {
		return l == 0 ? h[r] : sub(h[r], mul(h[l - 1], p[r - l + 1], mod), mod);
	}
};

typedef SlowHash<int(1e9 +  7), 31> hash7;
typedef SlowHash<int(1e9 +  9), 37> hash9;
typedef SlowHash<int(1e9 + 21), 41> hash21;
typedef SlowHash<int(1e9 + 33), 43> hash33;

template <int mod, int base>
int diff_pos(const SlowHash<mod, base> &a, const SlowHash<mod, base> &b) {
	int l = -1, r = min(a.n, b.n);
	while(r - l > 1) {
		int m = (l + r) >> 1;
		(a.get(0, m) == b.get(0, m) ? l : r) = m;
	}
	return r;
}



template <typename unsigned_type, unsigned_type base>
struct FastHash {
	int n; std::vector<unsigned_type> p, h;
	FastHash(const std::string &s) : n((int) s.size()), p(n, 1), h(n, n ? to_int(s[0]) : 0) {
		for(int i = 1; i < n; i++)  p[i] = p[i - 1] * base;
		for(int i = 1; i < n; i++)  h[i] = h[i - 1] * base + to_int(s[i]);
	}
	unsigned_type get(int l, int r) const {
		return l == 0 ? h[r] : h[r] - h[l - 1] * p[r - l + 1];
	}
};

typedef FastHash<uint32_t, 31> hash32;
typedef FastHash<uint64_t, 37> hash64;

template <typename utype, utype base>
int diff_pos(const FastHash<utype, base> &a, const FastHash<utype, base> &b) {
	int l = -1, r = min(a.n, b.n);
	while(r - l > 1) {
		int m = (l + r) >> 1;
		(a.get(0, m) == b.get(0, m) ? l : r) = m;
	}
	return r;
}
