#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 200005, M = 200005, C = 1000000005;

int rand(int a, int b){return a+rand()%(b-a+1);}

int main(int argc, char *argv[]){
  (argc > 1 ? srand(atoi(argv[1])) : srand(int(time(NULL))));
  ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);
  
  set<pair<int,int>> edges;
  int n = rand(1,N), m = rand(1,min(int(n*1LL*(n+1)/2),M));
  
  for(int i = 0; i < m; i++){
    int u = rand(1, n-1), v = rand(u+1, n);

    while(edges.count(make_pair(u,v)) || 
          edges.count(make_pair(v,u)))
      u = rand(1, n-1), v = rand(u+1, n);
    
    if(rand()%2)  edges.insert({u,v});
    else          edges.insert({v,u});
  }

  cout << n << " " << m << "\n";
  for(auto&[u, v] : edges)
    cout << u << " " << v << " " << rand(1, C) << "\n";
}