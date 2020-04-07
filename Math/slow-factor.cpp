using ll = long long;

vector<ll> factor(ll n){  // O(sqrt(N))
  vector<ll> r;
  for(ll i = 2; i*i <= d; i++)
    while(n%i == 0) r.push_back(i), n /= i;
  if(n > 1) r.push_back(n);
  return r;
}