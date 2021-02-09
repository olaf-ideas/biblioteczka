#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, m; cin >> n >> m;
	Dinic dinic(n, 0, n - 1);
	for(int i = 0; i < m; i++) {
		int u, v, c; cin >> u >> v >> c; u--, v--;
		dinic.add_edge(u, v, c);
	}
	cout << dinic.flow() << '\n';
}
