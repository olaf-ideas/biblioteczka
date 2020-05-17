#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
vector<int> adj[MAXN];
int sz[MAXN], dep[MAXN], fa[MAXN], dfn[MAXN], top[MAXN], id;

int ask_seg(int i, int l, int r, int x, int y){return 0;}

void dfs_sz(int u, int p = 0){
  sz[u] = 1, fa[u] = p;
  for(int v : adj[u]){
      if(u == p)  continue;
      dep[v] = dep[u]+1;
      dfs_sz(v, u);
  }
}

void dfs_hld(int u, int c, int p = 0){
    int s(-1);
    dfn[u] = ++id, top[u] = c;
    for(int v : adj[u])
        if(v != p && (s == -1 || sz[s] < sz[v]))    
            s = v;

    if(~s)    dfs_hld(s, c, u);
    for(int v : adj[u]){
        if(v != p && v != s)
            dfs_hld(v,v,u);
    }
}

int ask(int u, int v){
    int res = 0, fu = top[u], fv = top[v];
    while(fu != fv){
        if(dep[fu] < dep[fv])   swap(u, v), swap(fu, fv);
        res += ask_seg(1, 1, n, dfn[fu], dfn[u]);
        u += fa[fu], fu = top[u];
    }
    if(dep[u] > dep[v]) swap(u, v);
    res += ask_seg(1, 1, n, dfn[u], dfn[v]);
    return res;
}

int main(){

}