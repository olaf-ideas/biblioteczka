#include <bits/stdc++.h>
using namespace std;

typedef long long int LL;

struct P {
  int x, y;
  P() { }
  P(int _x, int _y) : x(_x), y(_y) { }
  bool operator < (const P& p) const { return x != p.x ? x < p.x : y < p.y; }
  bool operator == (const P& p) const { return x == p.x && y == p.y; }

  
};

LL det(const P& a, const P& b, const P& c) {
  return (b.x - a.x) * 1LL * (c.y - a.y) - (b.y - a.y) * 1LL * (c.x - a.x);
}

vector<P> convexHull(vector<P> p) {
  sort(p.begin(), p.end());
  vector<P> h;
  for(int i = 0; i < 2; i++) {
    auto start = h.size();
    for(const P& q : p) {
      while(h.size() >= start + 2 && det(h[h.size() - 2], h.back(), q) < 0) // < points on edges
        h.pop_back();
      h.push_back(q);
    }
    h.pop_back();
    reverse(p.begin(), p.end());
  }
  return h;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

  int n; cin >> n;
  vector<P> p;
  for(int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    p.push_back(P(x, y));
  }

  vector<P> h = convexHull(p);
  for(const P& q : h) {
    cout << q.x << ' ' << q.y << '\n';
  }
}
