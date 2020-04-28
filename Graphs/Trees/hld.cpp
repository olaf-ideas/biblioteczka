#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int N = 100005;

struct SegTree{
  SegTree(int _base) : base(_base){
    t.resize(base*2, 0);
  }

  void upd(int l, int r, int v, int x = 0, int y = -1, int u = 1){
    if(y == -1) y = base-1;
    if(r < x || y < l)  return;
    if(x <= l && r <= y){
      t[u] += v;
      return;
    }
    int m = (x+y)>>1;
    upd(l, r, v, x, m, u>>1);
    upd(l, r, v, m+1, y, u>>1|1);
  }

  int ask(int p){
    p += base;
    int r = 0;
    while(p)  r += t[p], p /= 10;
    return r;
  }

  int base;
  vector<int> t;
};

int n;
vector<int> adj[N];

struct HLD{
  vector<SegTree> trees;
  vector<int> h_adj[N];
  set<pair<int,int>> h_edges;
  pair<int,int> id[N];
  bool vis[N];
  int size[N], p[N], up[N][LOG], pre[N], post[N], cnt = 0;
  int light[N];

  bool is_anc(int u, int v){return pre[u] < pre[v] && post[u] > post[v];}

  int lca(int u, int v){
    if(is_anc(u, v))  return u;
    if(is_anc(v, u))  return v;
    for(int i = LOG-1; i >= 0; i--)
      if(!is_anc(up[u][i], v))  u = up[u][i];
    return up[u][0];
  }

  void dfs(int u){
    pre[u] = cnt++, size[u] = 1, up[u][0] = p[u];
    for(int i = 1; i < LOG; i++)  up[u][i] = up[up[u][i-1]][i-1];
    int h = -1, h_size = -1;
    for(int v : adj[u]) if(v != p[u]){
      p[v] = u;
      dfs(v);
      size[u] += size[v];
      if(h == -1 || size[v] > h_size) h = v, h_size = size[v];
    }
    if(h != -1){
      h_adj[h].push_back(u), h_adj[u].push_back(h);
      h_edges.insert(make_pair(u, h)), h_edges.insert(make_pair(h, u));
    }
    post[u] = cnt++;
  }
};
int n,q;
vector<int> adj[MAXN];

struct HLDTree{
    vector<SegTree> trees;
    vector<int> heavy[MAXN]; 
    set<pair<int,int>> heavy_edges;
    pair<int,int> node_id[MAXN];
    bool vis[MAXN];
    int size[MAXN], p[MAXN], up[MAXN][LOG], pre[MAXN], post[MAXN], cnt = 0;
    ll light[MAXN];

    bool is_ancestor(int u, int v){return pre[u] < pre[v] && post[u] > post[v];}

    int lca(int u, int v){
        if(is_ancestor(u, v))   return u;
        if(is_ancestor(v, u))   return v;
        for(int i = LOG-1; i >= 0; i--)
            if(!is_ancestor(up[u][i], v))   u = up[u][i];
        return up[u][0];
    }

    void dfs(int u){
        pre[u] = cnt++, size[u] = 1, up[u][0] = p[u];
        for(int i = 1; i < LOG; i++) up[u][i] = up[up[u][i-1]][i-1];

        int h = -1, h_size = -1;
        for(int v : adj[u]){
            if(v != p[u]){
                p[v] = u, dfs(v), size[u] += size[v];
                if(h == -1 || size[v] > h_size) h = v, h_size = size[v];
            }
        }
        if(h != -1){
            heavy[h].push_back(u), heavy[u].push_back(h);
            heavy_edges.insert(make_pair(u,h)), heavy_edges.insert(make_pair(h,u));
        }
        post[u] = cnt++;
    }

    int dfs_hld(int u, unordered_set<int> *h_nodes, int tree_id, int *tree_s, int id = 1){
        vis[u] = true, (*tree_s)++, h_nodes->insert(u), node_id[u] = make_pair(tree_id, id);
        int max_n = -1;
        bool any = false;
        for(int v : heavy[u]){
            if(!vis[v]){
                any = true;
                max_n = max(max_n, dfs_hld(v, h_nodes, tree_id, tree_s, id+1));
            }
        }
        if(any) return max_n;
        return u;
    }

    void build(){
        dfs(0);
        for(int i = 0; i < n; i++){
            if(vis[i] || heavy[i].size() != 1 || heavy[i][0] != p[i])    continue;
            unordered_set<int> h_path;
            int tree_s = 0, best = dfs_hld(i, &h_path, (int)trees.size(), &tree_s);
            trees.emplace_back(tree_s);
            trees.back().nodes = h_path, trees.back().best = best;
        }
    }

    void _update(int u, int anc, ll val){
        while(u != anc){
            while(!heavy_edges.count(make_pair(u,p[u])) && u != anc)    light[u]+=val, u = p[u];
            if(u == anc)    break;
            if(heavy_edges.count(make_pair(u,p[u]))){
                SegTree* curr_tree = &trees[node_id[u].first];
                if(curr_tree->nodes.count(anc)){
                    curr_tree->update(node_id[u].second, node_id[anc].second, val);
                    return;
                }else   curr_tree->update(node_id[u].second, curr_tree->base, val);
                u = p[curr_tree->best];
            }else   u = p[u];
        }
    }

    void update(int u, int v, ll val=1){
        int w = lca(u,v);
        _update(u,w,val), _update(v,w,val), light[w]+=val;
    }

    ll _query(int u, int anc){
        ll res = -INF;
        while(u != anc){
            while(!heavy_edges.count(make_pair(u,p[u])) && u != anc)    res = max(res, light[u]), u = p[u];
            if(u == anc)    break;
            if(heavy_edges.count(make_pair(u,p[u]))){
                SegTree* curr_tree = &trees[node_id[u].first];
                if(curr_tree->nodes.count(anc)){
                    res = max(res, curr_tree->query(node_id[u].second, node_id[anc].second));
                    return res;
                }else   res = max(res, curr_tree->query(node_id[u].second, curr_tree->base));
                u = p[curr_tree->best];
            }else   u = p[u];
        }
        return res;
    }

    ll query(int u, int v){
        int w = lca(u,v);
        return max({_query(u,w),_query(w,v), light[w]});
    }
};

HLDTree hld;

int main(){
    cin >> n;
    for(int i = 0; i < n-1; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    hld.build();

    cin >> q;
    while(q--){
        int type, u, v;
        cin >> type >> u >> v;
        u--,v--;
        if(type == 1)   hld.update(u,v);
        else            cout << hld.query(u,v) << "\n";
    }
}