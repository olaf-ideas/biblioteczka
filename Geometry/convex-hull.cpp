#include <bits/stdc++.h>
using namespace std;

bool isLeft(const pair<int, int>& a,
            const pair<int, int>& b,
            const pair<int, int>& c){
  return (b.first - a.first) * 1LL * (c.second - a.second) - 
         (b.second - a.second) * 1LL * (c.first - a.first) <= 0LL;   // < points on edges
}

vector<pair<int,int>> convexHull(vector<pair<int, int>> p){
  sort(p.begin(), p.end());
  vector<pair<int, int>> h;
  for(int i = 0; i < 2; i++){
    auto start = h.size();
    for(const pair<int, int> &q : p){
      while(h.size() >= start+2 && isLeft(h[h.size()-2], h[h.size()-1], q))
        h.pop_back();
      h.push_back(q);
    }
    h.pop_back();
    reverse(p.begin(), p.end());
  }
  return h;
}

int main(){
  int n;
  cin >> n;
  vector<pair<int, int>> p;
  for(int i = 0; i < n; i++){
    int x, y; cin >> x >> y;
    p.emplace_back(x, y);
  }
  vector<pair<int, int>> h = convexHull(p);

  cout << "convex hull:\n";
  for(const pair<int, int> q : h)
    cout << q.first << ' ' << q.second << '\n';
}
