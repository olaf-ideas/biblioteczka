using ll = long long;

ll pot_mod(ll a, ll b, ll m){
  ll r = 1;
  for(a %= m; b; b >>= 1,a = (a * a) % m)
    if(b & 1)r = (r * a) % m;
  return r;
}

ll pot(ll a, ll b){
  ll r = 1;
  for(; b; b >>= 1,a *= a)
    if(b & 1)r *= a;
  return r;
}

ll mod_inv(ll a, ll m){return pot_mod(a, m-2, m);}