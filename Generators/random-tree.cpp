#include <bits/stdc++.h>
using namespace std;
const int MINN = 100005, MAXN = 1000005; 

int rand(int a, int b){return a+rand()%(b-a+1);}

int main(int argc, char *argv[]){
  srand(atoi(argv[1]));
  ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);

  int n = rand(MINN,MAXN);
  cout << n << "\n";

  vector<pair<int,int>> edges;
  vector<int> perm(n+1);

  for(int i = 2; i <= n; i++) edges.emplace_back(rand(1,i-1),i);
  for(int i = 1; i <= n; i++) perm[i] = i;
  
  random_shuffle(perm.begin()+1, perm.end());
  random_shuffle(edges.begin(), edges.end());
  
  for(auto&[u, v] : edges){
    if(rand&1)  cout << u << " " << v << "\n";
    else        cout << v << " " << u << "\n";
  }
}