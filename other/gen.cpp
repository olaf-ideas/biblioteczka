#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define st first
#define nd second

using namespace std;

mt19937 rng;

inline int rand(const int &a, const int &b) { return uniform_int_distribution<int>(a, b)(rng); }
inline long long rand(const long long &a, const long long &b) { return uniform_int_distribution<long long>(a, b)(rng); }
inline double rand(const double &a, const double &b) { return uniform_real_distribution<double>(a, b)(rng); }
inline long double rand(const long double &a, const long double &b) { return uniform_real_distribution<long double>(a, b)(rng); }

vector<pair<int, int>> rand_tree(int n) {
	vector<pair<int, int>> edges;
	for(int i = 1; i < n; i++) {
		edges.pb(mp(rand(0, i - 1), i));
	}
	return edges;
}

vector<pair<int, int>> rand_conn_graph(int n, int m) {
	assert(m >= n - 1);
	vector<pair<int, int>> tree_edges = rand_tree(n);
	set<pair<int, int>> edges(tree_edges.begin(), tree_edges.end());
	
	while((int) edges.size() < m) {
		int u, v;
		do {
			u = rand(0, n - 2);
			v = rand(u + 1, n - 1);
		} while(edges.count(mp(u, v)));
		edges.insert(mp(u, v));
	}
	
	return vector<pair<int, int>>(edges.begin(), edges.end());
}

vector<pair<int, int>> rand_graph(int n, int m) {
	set<pair<int, int>> edges;
	int done_n = 0;
	while(done_n < n && m > 0) {
		int now_n = rand(1, min(m + 1, n - done_n));
		vector<pair<int, int>> tree = rand_tree(now_n);
		for(auto &it : tree)	edges.insert(mp(it.st + done_n, it.nd + done_n));
		done_n += (int) tree.size() + 1;
		m -= (int) tree.size();
	}
	while(m > 0) {
		int u, v;
		do {
			u = rand(0, n - 2);
			v = rand(u + 1, n - 1);
		} while(edges.count(mp(u, v)));
		edges.insert(mp(u, v));
		m--;
	}
	return vector<pair<int, int>>(edges.begin(), edges.end());
}

void shuffle_edges(int n, vector<pair<int, int>> &edges) {
	vector<int> ord(n);
	iota(ord.begin(), ord.end(), 1);
	shuffle(ord.begin(), ord.end(), rng);
	for(auto &it : edges) {
		it.st = ord[it.st], it.nd = ord[it.nd];
		if(rng() & 1)	swap(it.st, it.nd);
	}
	shuffle(edges.begin(), edges.end(), rng);
}

int main(int argc, char**argv) {
	ios::sync_with_stdio(false), cin.tie(nullptr);
	if(argc > 1)	rng.seed(atoi(argv[1]));
	else			rng.seed(random_device()());
	
	
	/* random array
	int n = rand(1, 7);
	cout << n << endl;
	for(int i = 0; i < n; i++) {
		cout << rand(1, 10) << " ";
	}
	cout << endl;
	*/
	
	/* random tree
	int n = rand(1, 7);
	cout << n << endl;
	vector<pair<int, int>> tree = rand_tree(n);
	shuffle_edges(n, tree);
	for(auto &it : tree) {
		cout << it.st << " " << it.nd << endl;
	}
	// */
	
	/* random connected graph
	int n = rand(1, 7), m = rand(n - 1, n * (n - 1) / 2);
	
	cout << n << " " << m << endl;
	vector<pair<int, int>> graph = rand_conn_graph(n, m);
	shuffle_edges(n, graph);
	for(auto &it : graph) {
		cout << it.st << " " << it.nd << endl;
	}
	// */
	
	/* random graph
	int n = rand(1, 7), m = rand(0, n * (n - 1) / 2);
	cout << n << " " << m << endl;
	vector<pair<int, int>> graph = rand_graph(n, m);
	shuffle_edges(n, graph);
	for(auto &&it : graph) {
		cout << it.st << " " << it.nd << endl;
	}
	// */
}
