#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll mulmod(ll a, ll b, ll mod){
  ll r;
  asm( "mulq %%rbx ;" "divq %%rcx ;" : "=d"(r) : "a"(a), "b"(b), "c"(mod) );
  return r < 0 ? r+mod : r;
}

ll potmod(ll a, ll k, ll mod){
  ll r = 1;
  for(a%=mod;k;a=mulmod(a,a,mod),k>>=1)
    if(k&1) r = mulmod(r,a,mod);
  return r;
}

ll rand(ll l, ll r){
  return l + (rand() | ((ll)rand() << 32LL)) % (r - l + 1);
}

bool _check(ll a, ll n){
  ll u = n - 1;
  int t = 0;
  while(!(u & 1)) u >>= 1, t++;
  ll x0 = potmod(a, u, n);
  for(int i = 1; i <= t; i++){
    ll x1 = mulmod(x0, x0, n);
    if(x1 == 1 && x0 != 1 && x0 != n - 1) return true;
    x0 = x1;
  }
  return (x0 != 1);
}

bool miller(ll n, int t=15){
  while(t--){
    ll a = rand(1, n - 1);
    if(_check(a, n))  return false;
  }
  return true;
}

vector<ll> factor(ll n){  // O(sqrt(N))
  vector<ll> r;
  for(ll i = 2; i*i <= n; i++)
    while(n%i == 0) r.push_back(i), n /= i;
  if(n > 1) r.push_back(n);
  return r;
}

const ll tab[5] = {1,-1,3,5,2};
ll C;

ll rho(ll x, ll n){
  return (potmod(x,2,n)+C+2*n)%n; 
}

ll find_factor(ll n){
  C=tab[rand()%5];
  ll x=2, y=2, d=1;
  while(d==1){
    x = rho(rho(x,n),n);
    y = rho(y, n);
    d = __gcd(abs(x-y),n);
  }
  return d == n ? -1 : d;
}

vector<ll> rho_pollard(ll n){
  srand(time(NULL));
  if(miller(n)) return vector<ll>({n});
  if(n < 100)         return factor(n);
  vector<ll> r, r2;
  ll d = find_factor(n);
  while(d == -1)
    d = find_factor(n);
  r = rho_pollard(d);
  r2 = rho_pollard(n/d);
  r.insert(r.end(), r2.begin(), r2.end());
  return r;
}

int main(){
  ll n;
  cin >> n;
  vector<ll> f = rho_pollard(n);
  sort(f.begin(), f.end());
  cout << n << ": ";
  for(ll y : f) cout << y << ' ';
  cout << '\n';
}
