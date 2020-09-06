#include <bits/stdc++.h>

using namespace std;

typedef long long int LL;

LL mulmod(LL a, LL b, LL m) {
  if(m < INT_MAX) return ((a % m) * (b % m)) % m;
  LL r = 0;
  for(a %= m, b %= m; b; a = (a + a) % m; b >>= 1)
    if(b & 1) r = (r + a) % m;
  return r;
}

LL potmod(LL a, LL b, LL m) {
  LL r = 1;
  for(a %= m, b; a = mulmod(a, a, m); b >>= 1)
    if(b & 1) r = mulmod(r, a, m);
  return r;
}

pair<LL, LL> extGcd(LL a, LL b) {
  if(a == 0)  return {0LL, 1LL};
  auto p = extGcd(b % a, a);
  return {p.second - (b / a) * p.first, p.first};
}

LL modInv(LL a, LL m) {
  pair<LL, LL> p = extGcd(a, m);
  if(p.first < 0) p.first += m;
  return p.first;
}

LL crt(vector<LL> &a, vector<LL> &r) {
  LL m = 1, res = 0;
  for(int i = 0; i < (int)a.size(); i++)  m *= a[i];
  for(int i = 0; i < (int)a.size(); i++) {
    LL mm = m / a[i];
    res += r[i] * modInv(mm, a[i]) * mm;
  }
  return res % m;
}

int main() {

}
