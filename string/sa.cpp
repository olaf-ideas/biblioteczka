#include <vector>
#include <string>
#include <algorithm>

std::vector<int> suffix_array(const std::string &s) {
	const int n = s.size();
	std::vector<int> sa(n), eqv(n), nexteqv(n);
	for(int i = 0; i < n; i++)  eqv[sa[i] = i] = s[i];
	int chunk = 1;
	auto cmp = [&chunk, n, &s, &eqv](const int &x, const int &y) {
		if(eqv[x] != eqv[y]) return eqv[x] < eqv[y];
		if(x + chunk >= n || y + chunk >= n) return x > y;
		return eqv[x + chunk] < eqv[y + chunk];
	};
	do {
		std::sort(sa.begin(), sa.end(), cmp);
		nexteqv[sa[0]] = 0;
		for(int i = 1; i < n; i++)  nexteqv[sa[i]] = nexteqv[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
		eqv.swap(nexteqv);
		chunk <<= 1;
	} while(eqv[sa[n - 1]] < n - 1);
	return sa;
}

std::vector<int> lcp(const std::string &s, const std::vector<int> &sa) {
	const int n = (int) s.size();
	std::vector<int> l(n), r(n);
	for(int i = 0; i < n; i++)  r[sa[i]] = i;
	for(int i = 0, c = 0; i < n; i++) {
		if(r[i] == n - 1)   l[r[i]] = 0;
		else {
			while(i + c < n && sa[r[i] + 1] + c < n &&
				  s[i + c] == s[sa[r[i] + 1] + c])  c++;
			l[r[i]] = c;
		}
		c = std::max(0, c - 1);
	}
	return l;
}
