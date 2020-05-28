// 100% legit no scam hungarian algorithm
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n, a[N][N], ans[N], cost, vis[N], matching_left[N], matching_right[N];

bool dfs(int u){
  vis[u]++;
  for(int i = 0; i < n; i++)
    if(!a[u][i]){
      if(matching_right[i] == -1 || (!vis[matching_right[i]] && dfs(matching_right[i])))
        return vis[u]--, matching_right[i] = u, true;
    }
  vis[u]--;
  return false;
}

bool left_vc[N], right_vc[N], vis_left[N], vis_right[N];

void konigDfs(int u, bool edge_type=false){
  if(edge_type) right_vc[u] = true, vis_right[u] = true;
  else          left_vc[u] = false, vis_left[u] = true;

  for(int i = 0; i < n; i++){
    if(!edge_type && !a[u][i] && matching_right[i] != u && !vis_right[i])   konigDfs(i, true);
    if( edge_type && !a[i][u] && matching_right[u] == i && !vis_left[i])    konigDfs(i, false);
  }
}

void vertexCover(){
  fill(left_vc, left_vc + n, true);
  fill(right_vc, right_vc + n, false);
  fill(vis_left, vis_left + n, false);
  fill(vis_right, vis_right + n, false);

  for(int i = 0; i < n; i++)
    if(matching_left[i] == -1)  konigDfs(i);
}

int find_matching(){
  fill(matching_left, matching_left + n, -1);
  fill(matching_right, matching_right + n, -1);
  fill(vis, vis + n, false);
  int cnt = 0;
  for(int i = 0; i < n; i++)
    cnt += dfs(i);
  for(int i = 0; i < n; i++)
    if(matching_right[i] != -1) matching_left[matching_right[i]] = i;

  return cnt;
}

void hungarian(){
  for(int i = 0; i < n; i++){
    int mn_row = INT_MAX;
    for(int j = 0; j < n; j++)  mn_row = min(mn_row, a[i][j]);
    for(int j = 0; j < n; j++)  a[i][j] -= mn_row;
  }

  for(int j = 0; j < n; j++){
    int mn_col = INT_MAX;
    for(int i = 0; i < n; i++)  mn_col = min(mn_col, a[i][j]);
    for(int i = 0; i < n; i++)  a[i][j] -= mn_col;
  }

  while(find_matching() != n){
    vertexCover();

    int mn = INT_MAX;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
        if(!left_vc[i] && !right_vc[j]) mn = min(mn, a[i][j]);

    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++){
        if( left_vc[i] &&  right_vc[j]) a[i][j] += mn;
        if(!left_vc[i] && !right_vc[j]) a[i][j] -= mn;
      }
  }

  for(int i = 0; i < n; i++)
    ans[i] = matching_left[i];
}

int b[N][N];

int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      cin >> a[i][j], b[i][j] = a[i][j];
  hungarian();

  for(int i = 0; i < n; i++)  cost += b[i][ans[i]];

  cout << cost << '\n';
  return 0;
  for(int i = 0; i < n; i++)
    cout << ans[i] << ' ';
  cout << '\n';
}
