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