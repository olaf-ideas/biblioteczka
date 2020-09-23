#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7, LOG = 17;

int n, q, k;
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

inline bool anc(int u, int v) { return pre[u] <= pre[v] && pos[u] >= pos[v]; }

int lca(int u, int v) {
    if(anc(u, v))   return u;
    if(anc(v, u))   return v;
    
    for(int i = LOG - 1; i >= 0; i--)
        if(!anc(p[u][i], v))    u = p[u][i];
    return p[u][0];
}

vector<int> adj_vt[N];
bool marked[N];
int cnt[N];

long long dfs2(int u, int f = -1) {
    long long ans = 0;

    cnt[u] = marked[u];
    for(int v : adj_vt[u]) if(v != f) {
        ans += dfs2(v, u);
        cnt[u] += cnt[v];
    }

    if(f != -1) {
        ans += (long long) (d[u] - d[f]) * cnt[u] * (k - cnt[u]);
    }

    return ans;
}

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
        cin >> k;
        vector<int> vert;
        for(int i = 0; i < k; i++) {
            int u; cin >> u;
            u--;
            marked[u] = true;
            vert.push_back(u);
        }

        sort(vert.begin(), vert.end(), [&](int u, int v) { return pre[u] < pre[v]; });
        for(int i = 0; i < k; i++) {
            vert.push_back(lca(vert[i], vert[i + 1]));
        }
        sort(vert.begin(), vert.end(), [&](int u, int v) { return pre[u] < pre[v]; });
        vert.erase(unique(vert.begin(), vert.end()), vert.end());  
 
        vector<int> tree;
        tree.push_back(vert[0]);

        // creating virtual tree
        for(int i = 1; i < (int) vert.size(); i++) {
            int u = vert[i];
            while(tree.size() >= 2 && !anc(tree.back(), u)) {
                adj_vt[tree[(int) tree.size() - 2]].push_back(tree.back());
                adj_vt[tree.back()].push_back(tree[(int) tree.size() - 2]);
                tree.pop_back();
            }
            tree.push_back(u);
        }

        while(tree.size() >= 2) {
            adj_vt[tree[(int) tree.size() - 2]].push_back(tree.back());
            adj_vt[tree.back()].push_back(tree[(int) tree.size() - 2]);
            tree.pop_back();
        }

        cout << dfs2(0) << '\n';

        for(int u : vert)   adj_vt[u].clear(), marked[u] = false;
    }
}
