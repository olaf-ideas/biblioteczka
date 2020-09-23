#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7, LOG = 17;

int n, q;
vector<int> adj[N];

int pre[N], pos[N], tim = 0, p[N][LOG], d[N];

void dfs(int u, int f) {
    p[u][0] = f;
    for(int i = 1; i < LOG; i++)    p[u][i] = p[p[u][i - 1]][i - 1];

    pre[u] = tim++;
    for(int v : adj[u]) if(v != f) {
        d[v] = d[u] + 1;
        dfs(v, u);
    }
    pos[u] = tim++;
}

bool anc(int u, int v) { return pre[u] <= pre[v] && pos[u] >= pos[v]; }

int lca(int u, int v) {
    if(anc(u, v))   return u;
    if(anc(v, u))   return v;

    for(int i = LOG - 1; i >= 0; i--)
        if(!anc(p[u][i], v))    u = p[u][i];
    return p[u][0];
}

vector<int> adj_vt[N];
vector<pair<int, int>> edges;
bool marked[N];

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    
    cin >> n;
    for(int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    cin >> q;
    while(q--) {
        int k; cin >> k;
        vector<int> x;
        for(int i = 0; i < k; i++) {
            int u; cin >> u;
            u--;
            marked[u] = true;
            x.push_back(u);
        }
        
        sort(x.begin(), x.end(), [&](int u, int v) { return pre[u] < pre[v]; });
        for(int i = 0; i < k - 1; i++) {
            x.push_back(lca(x[i], x[i + 1]));
        }
        sort(x.begin(), x.end(), [&](int u, int v) { return pre[u] < pre[v]; });
        x.erase(unique(x.begin(), x.end()), x.end());

        vector<int> tree;
        for(int u : x) {
            while((int) tree.size() >= 2 && !anc(tree.back(), u)) {
                edges.emplace_back(tree[(int) tree.size() - 2], tree.back());
                adj_vt[tree[(int) tree.size() - 2]].push_back(tree.back());
                adj_vt[tree.back()].push_back(tree[(int) tree.size() - 2]);
                tree.pop_back();
            }  
            tree.push_back(u);
        }
        while((int) tree.size() >= 2) {
            edges.emplace_back(tree[(int) tree.size() - 2], tree.back());
            adj_vt[tree[(int) tree.size() - 2]].push_back(tree.back());
            adj_vt[tree.back()].push_back(tree[(int) tree.size() - 2]);
            tree.pop_back();
        }

        bool ok = true;
        for(const pair<int, int> &e : edges) {
            if(marked[e.first] && marked[e.second] &&
               d[e.first] + d[e.second] - 2 * d[lca(e.first, e.second)] == 1) {
                ok = false;
                break;
            }
        }        

        if(!ok) cout << "-1\n";
        else {
            int ans = 0;
            for(int u : x) {
                // cerr << u << ": ";
                int cnt = 0;
                for(int v : adj_vt[u]) {
                    // cerr << v << ' ';
                    if(marked[v] && marked[u])  ans += (u < v);
                    else if(marked[v])          cnt++;
                }       
                if(cnt > 1) ans++;
                assert(cnt > 0 || marked[u]);
                // cerr << '\n';
            }
            cout << ans << '\n';
        }

        for(int u : x)  marked[u] = false, adj_vt[u].clear();
        edges.clear();
    }
}
