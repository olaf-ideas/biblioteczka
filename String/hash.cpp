// najwiekszy polski hasher
//
// zadanka: 
// Graffiti: https://solve.edu.pl/~sparingi/tasks/view/209

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<int MOD, int BASE>
struct MyHash {
  int n;
  vector<int> p, h;
  string s;
  MyHash(const string& _s) : n((int)_s.size()), p(_s.size(),1), h(_s.size(),_s[0]-'a'+1), s(_s) {
    for(int i = 1; i < n; i++)  p[i] = int((p[i - 1] * 1LL * BASE) % MOD);
    for(int i = 1; i < n; i++)  h[i] = int((h[i - 1] * 1LL * BASE + s[i] - 'a' + 1) % MOD);
  }
  int operator () () { return h.back(); }
  int operator () (int l, int r) {
    if(l == 0)  return h[r];
    return int(((h[r] - h[l - 1] * 1LL * p[r - l + 1]) % MOD + MOD) % MOD);
  }
  bool operator < (const MyHash& other) {
    if(s[0] != other.s[0])  return s[0] < other.s[0];
    int l = 0, r = min(n, other.n); 
    if(h[r - 1] == other.h[r - 1])  return n < other.n;
    while(r - l > 1){
      int m = (l + r) >> 1;
      (h[m] == other.h[m] ? l = m : r = m);
    }
    return s[l + 1] < other.s[l + 1];
  }
};

typedef MyHash<1000000007, 31> Hash7;
typedef MyHash<1000000009, 31> Hash9;

int main() {
  string a, b;
  cin >> a >> b;
  Hash7 ha(a), hb(b);
  cout << (ha < hb) << '\n';  
}
