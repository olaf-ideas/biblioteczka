#include <bits/stdc++.h>
using namespace std;

const int N = 505, INF = 1000000005;

int n, m;
int a[N][N];

int main(){
  cin >> n >> m;
  for(int i = 0; i < n; i++)  fill(a[i], a[i] + n, INF), a[i][i] = 0;

  for(int i = 0; i < m; i++){
    int u, v, w; cin >> u >> v >> w;
    u--, v--;
    a[u][v] = w;
    a[v][u] = w;
  }

  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      for(int k = 0; k < n; k++)
        a[i][j] = min(a[i][j], a[i][k] + a[k][j]);

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++)
      cout << a[i][j] << ' ';
    cout << '\n';
  }
}
