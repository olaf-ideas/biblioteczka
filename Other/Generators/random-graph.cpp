#include <bits/stdc++.h>

using namespace std;

typedef long long int LL;

const int N = 5e3;
const int M = 1e5;

inline int r(int l, int r) { return l + rand() % (r - l + 1); }

int main(int argc, char** argv) {
  srand(atoi(argv[1]));

  int n = r(1, N);
  int m = r(1, min(M / n, n) * n);

  printf("%d\n", n);
  for(int i = 0; i < n; i++) cout << r(0, 1e9) << '\n';
  printf("%d\n", m);

  vector<pair<int, int>> edges;
  unordered_set<LL> s;

  for(int i = 0; i < m; i++) {
    int u = r(1, n - 1);
    int v = r(u + 1, n);

    while(s.count(u * 1LL * (n + 1) + v)) u = r(1, n - 1), v = r(u + 1, n);
    s.insert(u * 1LL * (n + 1) + v);

    if(rand() & 1)  swap(u, v);
    edges.push_back({u, v});
  }

  random_shuffle(edges.begin(), edges.end());
  
  for(const pair<int, int>& e : edges) {
    printf("%d %d %d\n", e.first, e.second, r(0, 10000));
  }
}