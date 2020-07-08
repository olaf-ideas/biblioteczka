#include <bits/stdc++.h>
using namespace std;

const int T = 1 << 19, INF = 1000000005;

int t[T << 1], p[T << 1];

void lazy(int u){
  t[u] += u;
  if(u < T) p[u << 1] += p[u], p[u << 1 | 1] += p[u];
  p[u] = 0;
}

void upd(int l, int r, int v, int x=0, int y=T-1, int u=1){
  lazy(u);
  if(l > y || r < x)    return;
  if(l <= x && y <= r){
    p[u] += v, lazy(u);
    return;
  }  
  int m = (x + y) >> 1;
  upd(l, r, v, x, m, u << 1);
  upd(l, r, v, m + 1, y, u << 1 | 1);
  t[u] = max(t[u << 1], t[u << 1 | 1]);
}

int ask(int l, int r, int x=0, int y=T-1, int u=1){
  lazy(u);
  if(l > y || r < x)  return -INF;
  if(l <= x && y <= r)  return t[u];
  int m = (x + y) >> 1;
  return max(ask(l, r, x, m, u << 1), ask(l, r, m + 1, y, u << 1 | 1));
}
