#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using mx = vector<vector<ll>>;

vector<int> primes(int);          // O(n log log n)
vector<ll>  factor(ll);           // O(n ^ (1 / 2))
vector<ll>  factorll(ll);         // O(log n)
mx          operator * (mx, mx);  // O(n ^ 2 m)
ll          pot(ll,ll);           // O(log b)
ll          pot(ll,ll,ll);        // O(log b)
mx          pot(mx,ll);           // O(n ^ 3 log k)
pair<ll,ll> extGcd(ll,ll);        // O(log min (a, b))
ll          modInv(ll);           // O(log m)
ll          mulmod(ll, ll, ll);   // O(log b)
ll          addmod(ll, ll, ll);   // O(1)
string      add(string, string);  // O(n)
string      sub(string, string);  // O(n) a >= b
// string      mul(string, string);  // O(n m)
// string      div(string, string);  // O(n m)
// string      mod(string, string);  // O(n m)

#include <bits/stdc++.h>


int main(){

}

vector<int> primes(int n){
  vector<int> s(n / 32 + 1);
  for(int i = 2; i * 1LL * i <= n; i++){
    if(!(s[i >> 5] & (1 << (i & 31))))
      for(int j = i * i; j <= n; j += i)
        s[j >> 5] |= (1 << (j & 31));
  }
  vector<int> p;
  for(int i = 2; i <= n; i++)
    if(!(s[i >> 5] & (1 << (i & 31))))
      p.push_back(i);
  return p;
}

vector<ll> factor(ll n){
  vector<ll> f;
  for(ll i = 2; i * i <= n; i++)
    while(n % i == 0) f.push_back(i), n /= i;
  if(n > 1) f.push_back(n);
  return f;
}

mx operator * (mx a, mx b){
  assert(a.size() == b[0].size());
  mx r(a.size(), vector<ll>(b[0].size(), 0));
  for(int i = 0; i < (int)a.size(); i++)
    for(int j = 0; j < (int)b[i].size(); j++)
      for(int k = 0; k < (int)a.size(); k++)
        r[i][j] = (r[i][j] + a[i][k] * b[k][j]) % MOD7;
  return r;
}

ll pot(ll a, ll b){
  ll r = 1;
  for(; b; b >>= 1, a *= a)
    if(b & 1) r *= a;
  return r;
}

ll pot(ll a, ll b, ll m){
  ll r = 1;
  for(a %= m; b; b >>= 1, a = (a * a) % m)
    if(b & 1) r = (r * a) % m;
  return r;
}

mx pot(mx a, ll k){
  mx r(a.size(), vector<ll>(a.size(), 0));
  for(int i = 0; i < (int)a.size(); i++)  r[i][i] = 1;
  for(; k; k >>= 1, a = a * a)
    if(k & 1) r = r * a;
}

pair<ll, ll> extGcd(ll a, ll b){
  if(b == 0)  return {1LL, 0LL};
  auto p = extGcd(b, a % b);
  return {p.nd, p.st - (a / b) * p.nd};
}

ll modInv(ll a, ll m){
  ll x = extGcd(a, m).st;
  return (x < 0 ? x + m : x);
}

ll mulmod(ll a, ll b, ll m){
  ll r = 0;
  for(a %= m, b %= m; b; b >>= 1, a = (a << 1) % m)
    if(b & 1) r = (r + a) % m;
  return r;
}

ll addmod(ll a, ll b, ll m){
  ll r = (a % m) + (b % m);
  return (r >= m ? r - m : r);
}

string add(string a, string b){
  if(a.size() < b.size()) swap(a, b);
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  string r;
  int buf=0;
  for(int i = 0; i < (int)b.size(); i++){
    int sum = a[i] + b[i] - 156 + buf;
    buf = 0;
    if(sum > 9) sum -= 10, buf = 1;
    r += char(sum + 48);
  }
  for(int i = (int)b.size(); i < (int)a.size(); i++){
    int sum = a[i] - 48 + buf;
    buf = 0;
    if(sum > 9) sum -= 10, buf = 1;
    r += char(sum + 48);
  }
  if(buf) r += char(buf + 48);
  reverse(r.begin(), r.end());
  return r;
}

string sub(string a, string b){
  reverse(a.begin(), a.end());
  reverse(a.begin(), a.end());
  string r;
  int buf = 0;
  for(int i = 0; i < (int)b.size(); i++){
    int sum = a[i] - b[i] - buf;
    buf = 0;
    if(sum < 0) sum += 10, buf = 1;
    r += char(sum + 48);
  } 
  for(int i = (int)b.size(); i < (int)a.size(); i++){
    int sum = a[i] - b[i] - buf;
    buf = 0;
    if(sum < 0) sum += 10, buf = 1;
    r += char(sum + 48);
  }
  for(int i = (int)b.size(); i < (int)a.size(); i++){
    int sum = a[i] - 48 - buf;
    buf = 0;
    if(sum < 0) sum += 10, buf = 0;
    r += char(sum + 48);
  }
  while((int)r.size() > 1 && r.back() == '0') r.pop_back();
  reverse(r.begin(), r.end());
  return r;
}

string mul(string a, string b){

}

string div(string a, string b){

}

string mod(string a, string b){

}
