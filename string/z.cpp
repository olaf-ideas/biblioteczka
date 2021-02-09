#include <vector>
#include <string>

std::vector<int> z(const std::string &s) {
	const int n = (int) s.size();
	std::vector<int> Z(n);
	for(int l = 0, r = 0, i = 1; i < n; i++) {
		if(i > r) {
			l = r = i;
			while(r < n && s[r - l] == s[r])	r++;
			Z[i] = r - l; r--;
		} else {
			int k = i - l;
			if(Z[k] < r - i + 1)	Z[i] = Z[k];
			else {
				l = i;
				while(r < n && s[r - l] == s[r])	r++;
				Z[i] = r - l; r--;
			}
		}
	}
	return Z;
}
