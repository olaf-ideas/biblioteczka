#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int t[2*MAXN], n;

void build(){
  for(int i = n-1; i > 0; i--)  t[i] = max(t[i << 1], t[i << 1 | 1]);
}

void upd(int p, int v){
  for(t[p += n] = v; p > 1; p >>= 1)  t[p >> 1] = max(t[p], t[p ^ 1]);
}

int rmq(int l, int r){
  int ans = 0;
  for(l += n, r += n; l <= r; l >>= 1, r >>= 1){
    if(l&1) ans = max(ans, t[l++]);
    if(r&1) ans = max(t[r--], ans);
  }
  return ans;
}