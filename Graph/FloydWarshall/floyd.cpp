/*
 * Description: Floyd-Warshall algorithm for shortest path between pairs of vertices
 * Author: olaf_surgut
 * Complexity: O(N^3)
 * Verification: https://cses.fi/problemset/task/1672/ 
 */
const long long LONG_INF = 1e18 + 7;

template<class T>
void floydWarshall(vector<vector<T>> &a) {
    const int n = (int)a.size();
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
}
