/*
 * Desciption: 2-SAT problem solver
 * Author: olaf_surgut
 * Complexity: O(N + M)
 * Verification: https://cses.fi/problemset/task/1684 https://szkopul.edu.pl/problemset/problem/PaOm0b0Z7CvBDSQxwd1ItSP8/site/?key=statement
 */

struct SAT {
    int n;
    vector<vector<int>> adj;
    vector<int> ans;

    SAT(int _n) : n(_n), adj(2 * n) { }

    void either(int a, int b) { // zoga_mother.either(zoga, ~myszojelen);
        a = max(2 * a, -1 - 2 * a);
        b = max(2 * b, -1 - 2 * b);
        assert(0 <= a && a < 2 * n && 0 <= b && b < 2 * n);
        adj[a].push_back(b ^ 1);
        adj[b].push_back(a ^ 1);
    }

    void set_value(int x) { either(x, x); }

    vector<int> val, comp, z; int time = 0;
    int dfs(int u) {
        int low = val[u] = ++time, x; z.push_back(u);
        for(int v : adj[u]) if(!comp[v])
            low = min(low, val[v] ?: dfs(v));
        if(low == val[u]) do {
            x = z.back(); z.pop_back();
            comp[x] = low;
            if(ans[x >> 1] == -1) ans[x >> 1] = x & 1;
        } while(x != u);
        return val[u] = low;
    }

    bool solve() {
        ans.assign(n, -1);
        val.assign(2 * n, 0); comp = val;
        for(int i = 0; i < 2 * n; i++) if(!comp[i]) dfs(i);
        for(int i = 0; i < n; i++)  if(comp[2 * i] == comp[2 * i + 1])  return false;
        return true;
    }
};
