/*
https://github.com/the-tourist/algo/blob/master/data/sparsetable.cpp
Usage:
	SparseTable<int> table(a, [](int i, int j) { return min(i, j); });
*/
template <typename T, class F = function<T(const T&, const T&)>>
struct SparseTable {
	int n;
	std::vector<std::vector<T>> mat;
	F f;
	
	SparseTable(const vector<T> &a, const F &ff) : f(ff) {
		n = static_cast<int>(a.size());
		int max_log = 32 - __builtin_clz(n);
		mat.resize(max_log);
		mat[0] = a;
		for(int j = 1; j < max_log; j++) {
			mat[j].resize(n - (1 << j) + 1);
			for(int i = 0; i <= n - (1 << j); i++) {
				mat[j][i] = f(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
			}
		}
	}
	
	T ask(int l, int r) const {
		assert(0 <= l && l <= r && r <= n - 1);
		int lg = 32 - __builtin_clz(r - l + 1) - 1;
		return f(mat[lg][l], mat[lg][r - (1 << lg) + 1]);
	}
};
