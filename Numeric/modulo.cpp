#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll mulmod(ll a, ll b, ll m){
  if(m < INT_MAX) return ((a % m) * (b % m)) % m;
  ll r = 0;
  for(a %= m, b %= m; b; a = (a + a) % m; b >>= 1)
    if(b & 1) r = (r + a) % m;
  return r;
}

ll potmod(ll a, ll b, ll m){
  ll r = 1;
  for(a %= m, b; a = mulmod(a, a, m); b >>= 1)
    if(b & 1) r = mulmod(r, a, m);
  return r;
}

pair<ll, ll> extGcd(ll a, ll b){
  if(a == 0)  return {0LL, 1LL};
  auto p = extGcd(b % a, a);
  return {p.second - (b / a) * p.first, p.first};
}

ll modInv(ll a, ll m){
  pair<ll, ll> p = extGcd(a, m);
  if(p.first < 0) p.first += m;
  return p.first;
}

ll crt(vector<ll> &a, vector<ll> &r){
  ll m = 1, res = 0;
  for(int i = 0; i < (int)a.size(); i++)  m *= a[i];
  for(int i = 0; i < (int)a.size(); i++){
    ll mm = m / a[i];
    res += r[i] * modInv(mm, a[i]) * mm;
  }
  return res % m;
}

int main(){

}
