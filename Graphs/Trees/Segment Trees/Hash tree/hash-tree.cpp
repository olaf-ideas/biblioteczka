#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class HashTree{
private:
  const int MOD = 1000000009, ALF = 31;
  vector<int> h, p, s;
  int b = 1, n;
public:
  HashTree(const string& t){
    n = (int)t.size();
    while(b <= n)  b <<= 1;
    h.resize(2*b+5);
    p.resize(2*b+5);
    s.resize(2*b+5);

    p[0] = 1;
    for(int i = 1; i <= b; i++) p[i] = int((p[i-1] * 1LL * ALF) % MOD);
  
    for(int i = 0; i < n; i++)  h[i+b] = t[i] - 'a' +1;
    for(int i = b; i < (b<<1); i++) s[i] = 1;
    for(int i = b-1; i > 0; i--){
      s[i] = s[i<<1]<<1;
      h[i] = int((h[i<<1] + h[i<<1|1] * 1LL * p[s[i<<1]]) % MOD);
    }
  }
  
  void upd(int x, char ch){
    for(h[x += b] = ch - 'a' +1; x >>= 1;)
      h[x] = int((h[x<<1] + h[x<<1|1] * 1LL * p[s[x<<1]]) % MOD);
  }

  int ask(int l, int r){
    int lth = r-l+1;
    pair<int,int> rl = make_pair(0,0), rr = make_pair(0,0);
    for(l += b-1, r += b+1; l/2 != r/2; l >>= 1, r >>= 1){
      if(!(l&1)){
        rl.second += s[l+1];
        rl.first = int((rl.first + h[l+1] * 1LL * p[rl.second - s[l+1]]) % MOD);
      }
      if(r&1){
        rr.second += s[r-1];
        rr.first = int((rr.first + h[r-1] * 1LL * p[lth-rr.second]) % MOD);
      }
    }
    return (rl.first + rr.first) % MOD;
  }
};

int main(){
  // ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);

  string s;
  cin >> s;
  HashTree h(s);


  for(int i = 0; i < (int)s.size(); i++){
    string a;
    for(int j = i; j < (int)s.size(); j++){
      a += s[j];
      for(int k = 0; k < (int)s.size(); k++){
        string b;
        for(int l = k; l < (int)s.size(); l++){
          b += s[l];
          bool x = (h.ask(i, j) == h.ask(k, l));
          bool y = (a == b);
          if(x != y)  cout << a << " " << b << " hash:" << x << " normal: " << y << "\n";
        }
      }
    }
  }
}