using ll = long long;

ll mul(ll a, ll b, ll mod){
  ll r;
  asm( "mulq %%rbx ;" "divq %%rcx ;" : "=d"(r) : "a"(a), "b"(b), "c"(mod) );
  return r < 0 ? r+mod : r;
}

ll pot_mod(ll a, ll k, ll mod){
  ll r = 1;
  for(a%=mod;k;a=mul(a,a,mod),k>>=1)
    if(k&1) r = mul(r,a,mod);
  return r;
}

bool miller_rabin(ll n){
  int p[11] = {2,3,5,7,11,13,17,19,23,29,31};
  if(n < 32){
    for(int i = 0; i < 11; i++)
      if(a[i] == n) return true;
    return false;
  }
  if(n%2 == 0)  return false;
  ll s = (n-1)&(-(n-1));
  ll d = (n-1)/s;
  for(int k = 0; k < 11; k++){
    ll x = (a[k],d,n);
    if(__gcd(x,n) != 1) return false;
    if(x != 1 && x != n-1){
      int i = 0;
      for(;1LL<<i < s; i++){
        x = mul(x,x,n);
        if(x == 1 || x == 0)  return false;
        if(x == n-1)  break;
      }
      if(1LL<<i == s && x != n-1) return false;
    }
  }
  return true;
}

vector<ll> factor(ll n){  // O(sqrt(N))
  vector<ll> r;
  for(ll i = 2; i*i <= d; i++)
    while(n%i == 0) r.push_back(i), n /= i;
  if(n > 1) r.push_back(n);
  return r;
}

const ll tab[5] = {1,-1,3,5,2};
ll C;

ll rho(ll x, ll n){
  return (pot_mod(x,2,n)+C+2*n)%n; 
}

ll find_factor(ll n){
  C=tab[rand()%5];
  ll x=2, y=2, d=1;
  while(d==1){
    x = rho(rho(x,n),n);
    y = rho(y, n);
    d = gcd(abs(x-y),n);
  }
  return d == n ? -1 : d;
}

vector<ll> rho_pollard(ll n){
  srand(time(NULL));
  if(miller_rabin(n)) return vector<ll>({n});
  if(n < 100)         return factor(n);
  vector<ll> r, r2;
  ll d = find_factor(n);
  while(d == -1)
    d = find_factor();
  r = rho_pollard(d);
  r2 = rho_pollard(n/d);
  r.insert(r.end(), r2.begin(), r2.end());
  return r;
}