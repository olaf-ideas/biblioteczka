#include <string>
#include <vector>

int lcs(const string &s, const string &t) {
	const int n = (int) s.size(), m = (int) t.size();
	if(n < m)	return lcs(t, s);
	vector<vector<int>> dp(2, vector<int>(m + 1));
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(s[i - 1] == t[j - 1])	dp[i & 1][j] = dp[(i ^ 1) & 1][j - 1] + 1;
			else						dp[i & 1][j] = max(dp[i & 1][j - 1], dp[(i ^ 1) & 1][j]);
		}
	}
	return dp[n & 1][m & 1];
}
