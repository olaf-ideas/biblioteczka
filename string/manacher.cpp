/**
 * Author: olaf-ideas
 * License: CC0
 * Description: Manacher algorithm for the longest palindrome array
 * Complexity: O(|s|)
 * Status: tested
 */

#include <vector>
#include <string>
#include <algorithm>

std::vector<int> manacher_even(const std::string &s) {
	std::string x = "$" + s + "#";

	std::vector<int> r(1);
	for(int i = 1, j = 0; i < (int) x.size(); ) {
		while(x[i - j] == x[i + j + 1]) j++;
		r.push_back(j);
		int k = 1;
		while(r[i - k] != r[i] - k && k <= j)
			r.push_back(std::min(r[i - k], r[i] - k)), k++;
		j = std::max(0, j - k), i += k;
	}

	r.erase(r.begin()), r.pop_back();
	return r;
}

std::vector<int> manacher_odd(const std::string &s) {
	std::string x = "$" + s + "#";
	std::vector<int> r(1);
	for(int i = 1, j = 0; i < (int) x.size(); ) {
		while(x[i - j - 1] == x[i + j + 1]) j++;
		r.push_back(j);
		int k = 1;
		while(r[i - k] != r[i] - k && k <= j)
			r.push_back(std::min(r[i - k], r[i] - k)), k++;
		j = std::max(j - k, 0), i += k;
	}
	r.erase(r.begin()), r.pop_back();
	return r;
}
