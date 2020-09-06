#include <bits/stdc++.h>

using namespace std;

const int N = 1e5;

inline int r(int a, int b) { return a + rand() % (b -a + 1 ); }

int main(int argc, char* argv[]) {
  srand(atoi(argv[1]));

  int n = r(1, N);
  vector<pair<int,int>> e(n - 1);
  vector<int> p(n);

  for(int i = 1; i < n; i++)  e[i - 1] = {r(0, i - 1), i};
  for(int i = 1; i < n; i++)  p[i] = i + 1;

  random_shuffle(p.begin(), p.end());
  random_shuffle(e.begin(), e.end());
  
  printf("%d\n", n);
  for(const pair<int, int>& a : e) {
    int u = a.first, v = a.second;
    if(rand() & 1)  swap(u, v);
    printf("%d %d\n", p[u], p[v]);
  }
}
