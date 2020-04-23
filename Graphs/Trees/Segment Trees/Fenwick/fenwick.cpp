// Fenwick tree updata: O(log n), query: O(log n)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Fenwick{
  int n;
  vector<ll> t;
  Fenwick(int _n):n(_n),t(_n,0){}
  ll sum(int r){
    ll ans = 0;
    for(;r>0;r&=r-1)    ans += t[r-1];
    return ans;
  }
  ll sum(int l, int r){
    return sum(r) - sum(l-1);
  }
  void add(int k, ll x){
    for(;k<n;k|=k+1)    t[k] += x;
  }
  int lower_bound(ll sum){
    assert(sum >= 0);
    int pos = 0;
    for(int p = (1<<25);p;p>>=1)
      if(pos+p <= (int)t.size() && t[pos+p-1] < sum)
        pos += p, sum -= t[pos-1];
    return pos;
  }
};


int main(){
}