/*
 * Desciption: Tarjan algorithm for 2-SAT problem
 * Author: olaf_surgut
 * Complexity: O(N + M)
 * Verification: https://cses.fi/problemset/task/1684 https://szkopul.edu.pl/problemset/problem/PaOm0b0Z7CvBDSQxwd1ItSP8/site/?key=statement
 */

struct SAT {
    int n;
    vector<vector<int>> adj;
    stack<int> s;
    vector<int> pre, low, scc, vis;
    int tim = 1, cnt = 0;
    
    SAT(int _n) : n(_n), adj(n << 1), pre(n << 1), 
            low(n << 1), scc(n << 1), vis(n << 1) { }

    void dfs(int u) {
        low[u] = pre[u] = tim++;
        vis[u] = true;
        s.push(u);
        for(int v : adj[u]) {
            if(!pre[v]) dfs(v);
            if(vis[v])  low[u] = min(low[u], low[v]);
        }

        if(low[u] == pre[u]) {
            int v = -1;
            while(v != u) {
                v = s.top(); s.pop();
                vis[v] = false, scc[v] = cnt;
            }
            cnt++;
        }
    }

    // Note: even index -> negation, odd index -> normal, nu = true -> u is false
    void ae2(int u, bool nu, int v, bool nv) { // u is nu or v is nv
        assert(0 <= u && u < n && 0 <= v && v < n);
        adj[2 * u + nu].push_back(2 * v + 1 - nv);
        adj[2 * v + nv].push_back(2 * u + 1 - nu);
    }

    void always_true(int u) {
        assert(0 <= u && u < n);
        ae(u, false, u, false);
    }

    void always_false(int u) {
        assert(0 <= u && u < n);
        ae(u, true, u, true);
    }

    bool solve(vector<bool> &ans) {
        for(int i = 0; i < 2 * n; i++) if(!pre[i]) dfs(i);
        for(int i = 0; i < n; i++) if(scc[2 * i] == scc[2 * i + 1]) return false;
        vector<int> v(cnt), c(cnt, -1);
        for(int i = 0; i < 2 * n; i++)  v[scc[i]] = i;
        for(int i = 0; i < cnt; i++) if(c[i] == -1) c[i] = true, c[scc[v[i] ^ 1]] = false;
        ans.resize(n, false);
        for(int i = 0; i < n; i++) ans[i] = c[scc[2 * i + 1]];
        return true;
    }
};
