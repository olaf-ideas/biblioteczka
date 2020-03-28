#include <bits/stdc++.h>
using namespace std;

bool is_left(const pair<int,int>& a,
             const pair<int,int>& b,
             const pair<int,int>& c){
  return (b.first-a.first)*(c.second-a.second) - (b.second-a.second)*(c.first-a.first) < 0;   // <= jesli chcemy punkty na krawedziach 
}

vector<pair<int,int>> convex_hull(vector<pair<int,int>> pts){
  sort(pts.begin(), pts.end());
  vector<pair<int,int>> h;
  for(int i = 0; i < 2; i++){
    auto start = h.size();
    for(const auto& p : pts){
      while(h.size() >= start+2 && is_left(h[h.size()-2], h[h.size()-1], p) <= 0)
        h.pop_back();
      h.push_back(p);
    }
    h.pop_back();
    reverse(pts.begin(), pts.end());
  }
  return h;
}

int main(){

}