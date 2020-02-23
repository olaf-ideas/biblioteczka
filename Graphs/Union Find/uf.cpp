#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int uf[MAXN], s[MAXN];

int find_(int u){return uf[u] == u ? u : uf[u] = find_(uf[u]);}

void union_(int u, int v){
    u = find_(u), v = find_(v);
    if(u != v){
        if(s[u] < s[v])   swap(u,v);
        uf[u] = uf[v];
        s[u] += s[v];
    }
}

void union_2(int u, int v){
    u = find_(u), v = find_(v);
    if(rand()&1)    swap(u,v);
    uf[u] = uf[v];
}

int main(){

}