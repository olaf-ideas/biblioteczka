#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;

int n, m;
vector<int> adj[MAXN];

bool check_pb(){
    bool ans = true;
    queue<int> q;
    vector<int> side(n, -1);

    for(int i = 0; i < n; i++){
        if(side[i] == -1){
            q.push(i);
            side[i] = 0;
            while(!q.empty()){
                int u = q.front();
                q.pop();
                for(int v : adj[u]){
                    if(side[v] == -1)   side[v] = side[u] ^ 1, q.push(u);
                    else                ans &= side[v] != side[u];
                }
            }
        }
    }

    return ans;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if(check_pb())  printf("Bipartie graph\n");
    else            printf("Not bipartie graph\n");
}