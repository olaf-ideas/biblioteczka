/*
 * Description: Floyd-Warshall algorithm for shortest path between pairs of vertices
 * Author: olaf_surgut
 * Complexity: O(N^3)
 * Verification: https://cses.fi/problemset/task/1672/ 
 */

#include <bits/stdc++.h>

using namespace std;

const long long LONG_INF = 1e18 + 7;

template<class T>
void floydWarshall(vector<vector<T>> &a) {
    const int n = (int)a.size();
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
}

int n, m, q;
vector<vector<long long>> a;

int main() {
    scanf("%d %d %d", &n, &m, &q);
    a.resize(n, vector<long long>(n, LONG_INF));
    for(int i = 0; i < n; i++)  a[i][i] = 0;

    for(int i = 0; i < m; i++) {
        int u, v, w; scanf("%d %d %d", &u, &v, &w);
        u--, v--;
        a[u][v] = min(a[u][v], (long long) w);
        a[v][u] = min(a[v][u], (long long) w);
    }

    floydWarshall(a);

    while(q--) {
        int u, v; scanf("%d %d", &u, &v);
        u--, v--;
        if(a[u][v] >= LONG_INF) puts("-1");
        else                    printf("%lld\n", a[u][v]);
    }

}
