/**
 * Author: olaf-ideas
 * License: CC0
 * Description: Knuth Morris Pratt algorithm 
 * Complexity: O(|s|) | O(|s| + |t|)
 * Status: tested
 */

#include <vector>
#include <string>

std::vector<int> kmp(const std::string &s) {
	std::vector<int> p(s.size());
	for(int i = 1, d = 0; i < (int) s.size(); i++) {
		while(d > 0 && s[i] != s[d])	d = p[d - 1];
		if(s[i] == s[d])	d++;
		p[i] = d;
	}
	return p;
}

// pattern | text
std::vector<int> kmp(const std::string &s, const std::string &t) {
	if(s.size() > t.size()) return {};
	int n = (int) s.size(), m = (int) t.size();
	std::vector<int> p = kmp(s), r;
	for(int i = 0, d = 0; i < m; i++) {
		while(d > 0 && (d == n || t[i] != s[d]))	d = p[d - 1];
		if(t[i] == s[d])	d++;
		if(d == n)	r.push_back(i - n + 1);
	}
	return r;
}
