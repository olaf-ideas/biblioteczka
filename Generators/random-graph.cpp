#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 200005, M = 200005, C = 1000000005;

int rand(int a, int b){return a+rand()%(b-a+1);}

int main(int argc, char *argv[]){
  ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);
  srand(atoi(argv[1]));

  set<pair<int,int>> edges;
  int n = rand(1,N), m = rand(1,min(M, (n*(n-1))>>1));
  
  cout << n << " " << m << "\n";

  for(int i = 0; i < m; i++){
    int u = rand(1,n), v = rand(1,n);

    while(u == v || edges.count(make_pair(u,v)) || 
                    edges.count(make_pair(u,v)))
      v = rand(1, n), u = rand(1, n);
    
    edges.insert(make_pair(u,v));
  }

  for(auto&[u, v] : edges)
    cout << u << " " << v << " " << rand(1, C) << "\n";
}