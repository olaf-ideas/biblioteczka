#include <bits/stdc++.h>
using namespace std;

const int N = 20, INF = 1000000005;

int n, m, adj[N][N];

int dp[(1<<N)];

void tsp(){
  fill(dp, dp + (1 << n), INF);
  for(int i = 1; i < (1 << n); i <<= 1)
    dp[i] = 0;

  for(int i = 1; i < (1 << n); i++){
    for(int j = 0; j < n; j++){
      if(i & (1 << j))  continue;
      for(int k = 0; k < n; k++){
        if(i & (1 << k)){
          dp[i ^ (1 << k)] = min(dp[i ^ (1 << k)], dp[i] + adj[j][k]);
        }
      }
    }
  }

  cout << dp[(1 << n) - 1] << '\n';
}

int main(){
  cin >> n >> m;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      adj[i][j] = INF;

  for(int i = 0; i < m; i++){
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    adj[u][v] = w;
    adj[v][u] = w;
  }
  tsp();
}
