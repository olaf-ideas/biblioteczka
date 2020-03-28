#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int uf[N];

int find_uf(int u){return uf[u]==u?u:uf[u]=find_(uf[u]);}
void union_uf(int u, int v){(uf[find_(u)]=uf[find_(v)];}

int main(){

}