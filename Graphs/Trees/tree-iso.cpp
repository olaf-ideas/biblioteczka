// Tree Isomorphism build: O(n) (nie debugowane)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100005;

int m[MAXN], num = 1;
vector<int> seed;

struct TreeIso{
    struct Hash{
        ll a, b, c;
        Hash operator + (const ll &v) const {
            return {a^v,b+v*v,c+v*v*v};
        }
        bool operator == (const Hash& h) const {
            return (a == h.a && b == h.b && c == h.c);
        }
    };

    vector<int> s, id;
    vector<vector<pair<int,int>>> adj;
    vector<Hash> h;
    int n;

    TreeIso(int _n):n(n),s(n+5),id(n+5),adj(n+5),h(n+5){}

    void build(){
        for(int i = 0; i < n-1; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u].push_back(make_pair(v,adj[v].size()));
            adj[v].push_back(make_pair(u,adj[u].size()));
        }
    }

    void calcSizes(int u = 0, int p = -1){
        s[u] = 1;
        for(const pair<int,int>& e : adj[u]){
            int v = e.first;
            if(v == p)  continue;
            calcSizes(v, u);
            s[u] += s[v];
        }
    }

    void dfs(int u, int p){
        for(const pair<int,int>& e : adj[u]){
            int v = e.first;
            if(v == p)  continue;
            dfs(v, u);
            h[v] = h[v] + seed[id[u]];
        }
        ll hash = ((h[u].a + h[u].b + h[u].c) % MAXN + MAXN) % MAXN;
        int* x = &m[hash];
        if(x == 0){
            *x = num;
            id[u] = num++;
        }else   id[u] = *x;
    }

    void erase(int u, int i){
        swap(adj[u][i], adj[u].back());
        adj[u].pop_back();
    }

    pair<int,int> centroids(int u = 1, int p = -1){
        calcSizes(1, -1);
        int tot = s[u];
        bool ok = true;
        while(ok){
            ok = false;
            for(const pair<int,int>& e : adj[u]){
                int v = e.first, id = e.second;
                if(v != p && s[v]*2 > tot){
                    p = u, u = v, ok = true;
                    break;
                }
                if(s[v]*2 == tot){
                    erase(u, adj[v][id].second);
                    erase(u, id);
                    return make_pair(v,u);
                }
            }
        }
        return make_pair(u,u);
    }

    Hash hash(){
        pair<int,int> c = centroids(1,1);
        adj[0].push_back(make_pair(c.first, 0));
        adj[0].push_back(make_pair(c.second, 0));
        dfs(0, -1);
        return h[0];
    }
};

void initSeed(){
    for(int i = 0; i < MAXN; i++)   seed.push_back(i+1);
    random_shuffle(seed.begin(), seed.end());
}

int main(){

}