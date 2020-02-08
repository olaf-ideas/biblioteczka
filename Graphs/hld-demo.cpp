#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN = 500005, INF = (1LL<<60LL);

struct SegTree{
    SegTree(int _base){
        while(base < _base) base <<= 1;
        t.resize(base<<1,0);
        l.resize(base<<1,0);
    }

    int base = 1;
    vector<ll> t,l;
    unordered_set<int> nodes;
    int best;

    void lazy(int u){
        t[u] += l[u];
        if(u < MAXN)    l[u<<1] += l[u], l[u<<1|1] += l[u];
        l[u] = 0;
    }

    void update(int a, int b, ll val, int low = 0, int high = -1, int u = 1){
        lazy(u);
        if(high == -1)  high = base-1;
        if(a > high || b < low) return;
        if(a <= low && high <= b){
            l[u] += val;
            lazy(u);
            return;
        }
        int mid = (low+high)>>1;
        update(a,b,val,low,mid,u<<1);
        update(a,b,val,mid+1,high,u<<1|1);
    }

    ll query(int a, int b, int low = 0, int high = -1, int u = 1){
        lazy(u);
        if(high == -1)  high = base-1;
        if(a > high || b < low)     return -INF;
        if(a <= low && high <= b)   return t[u];
        int mid = (low+high)>>1;
        return max(query(a,b,low,mid,u<<1), query(a,b,mid+1,high,u<<1|1));
    }

    void update(int x, ll val){update(x,x,val);}
    ll query(int x){return query(x,x);}
};

int n,q;
vector<int> adj[MAXN];

struct LCA{
    int up[MAXN][35], pre[MAXN], post[MAXN], cnt = 0;
    void build(int u = 0, int p = 0){
        pre[u] = cnt++;
        up[u][0] = p;
        for(int i = 1; i < 35; i++) up[u][i] = up[up[u][i-1]][i-1];

        for(int v : adj[u])
            if(v != p)  build(v, u);
        post[u] = cnt++;
    }

    bool is_ancestor(int u, int v){
        return pre[u] < pre[v] && post[u] > post[v];
    }
    
    int query(int u, int v){
        if(is_ancestor(u, v))   return u;
        if(is_ancestor(v, u))   return v;
        for(int i = 34; i >= 0; i--)
            if(!is_ancestor(up[u][i], v))   u = up[u][i];
        return up[u][0];
    }
};

struct HLDTree{
    LCA lca;
    vector<SegTree> trees;
    vector<int> heavy[MAXN];
    set<pair<int,int>> heavy_edges;
    pair<int,int> node_id[MAXN];
    bool vis[MAXN];
    int size[MAXN], p[MAXN];
    ll light[MAXN];

    void dfs(int u){
        vis[u] = true, size[u] = 1;
        int h = -1, h_size = -1;

        for(int v : adj[u]){
            if(!vis[v] && v != p[u]){
                p[v] = u;
                dfs(v);
                size[u] += size[v];
                if(h == -1 || size[v] > h_size) h = v, h_size = size[v];
            }
        }
        if(h != -1){
            heavy[h].push_back(u);
            heavy[u].push_back(h);
            heavy_edges.insert(make_pair(u,h));
            heavy_edges.insert(make_pair(h,u));
        }
    }

    int dfs_hld(int u, unordered_set<int> *h_nodes, int tree_id, int *tree_s, int height = 0){
        vis[u] = true, (*tree_s)++;
        h_nodes->insert(u), node_id[u] = make_pair(tree_id, height);
        int max_h = -1;
        bool any = false;
        for(int v : heavy[u]){
            if(!vis[v]){
                any = true;
                max_h = max(max_h, dfs_hld(v, h_nodes, tree_id, tree_s, height+1));
            }
        }
        if(any) return max_h;
        return u;
    }

    void build(){
        cout << "building hld...\n";
        lca.build();
        cout << "lca preprocessing done\n";
        fill(vis,vis+MAXN,false);
        fill(light,light+MAXN,0);
        dfs(0);
        cout << "heavy edges:\n";
        for(const pair<int,int>& edge : heavy_edges)
            cout << edge.first << " - " << edge.second << "\n";

        fill(vis,vis+MAXN,false);
        for(int i = 0; i < n; i++){
            if(vis[i])  continue;
            if(heavy[i].size() != 1)    continue;
            if(heavy[i][0] != p[i])     continue;
            unordered_set<int> h_nodes;
            int tree_s = 0, best = dfs_hld(i,&h_nodes, (int)trees.size(), &tree_s);
            trees.emplace_back(tree_s);
            trees.back().nodes = h_nodes;
            trees.back().best = best;
        }
        cout << "hld preprocessing done\n";
    }

    void _update(int u, int anc, ll val){
        while(u != anc){
            while(!heavy_edges.count(make_pair(u,p[u])) && u != anc)
                light[u]+=val, u = p[u];
            if(u == anc)    break;
            if(heavy_edges.count(make_pair(u,p[u]))){
                SegTree* curr_tree = &trees[node_id[u].first];
                if(curr_tree->nodes.count(anc)){
                    curr_tree->update(node_id[u].second, node_id[anc].second-1, val);
                    return;
                }else   curr_tree->update(node_id[u].second, curr_tree->base-1, val);
                u = p[curr_tree->best];
            }else   u = p[u];
        }
    }

    void update(int u, int v, ll val=1){
        int w = lca.query(u,v);
        cout << "new update: " << u << " - " << v << "\n";
        cout << " > update: " << u << " - " << w << "\n"; 
        cout << " > update: " << v << " - " << w << "\n";
        _update(u,w,val);
        _update(v,w,val);
        light[w]+=val;
    }

    ll _query(int u, int anc){
        ll res = -INF;
        while(u != anc){
            while(!heavy_edges.count(make_pair(u,p[u])) && u != anc)
                res = max(res, light[u]), u = p[u];
            if(u == anc)    break;
            if(heavy_edges.count(make_pair(u,p[u]))){
                SegTree* curr_tree = &trees[node_id[u].first];
                if(curr_tree->nodes.count(anc)){
                    res = max(res, curr_tree->query(node_id[u].second, node_id[anc].second-1));
                    return res;
                }else   res = max(res, curr_tree->query(node_id[u].second, curr_tree->base-1));
                u = p[curr_tree->best];
            }else   u = p[u];
        }
        return res;
    }

    ll query(int u, int v = -1){
        if(v == -1) return light[u];
        int w = lca.query(u,v);

        cout << "new query: " << u << " - " << v << "\n";
        cout << " > query: " << u << " - " << w << "\n"; 
        cout << " > query: " << v << " - " << w << "\n";
        return max({_query(u,w), _query(v,w), light[w]});
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
        if(type == 1)  hld.update(u,v);
        else   cout << hld.query(u,v) << "\n";
    }

}