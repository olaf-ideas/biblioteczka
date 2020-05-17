using ll = long long;

pair<ll,ll> ext_gcd(ll a, ll b){
    if(b == 0)  return {1LL, 0LL};
    auto p = ext_gcd(b, a%b);
    return {p.second, p.first-(a/b)*p.second};
}

ll mod_inv(ll a, ll m){
    pair<ll,ll> p = ext_gcd(a,m);
    if(p.first < 0) p.first += m;
    return p.first;
}

ll mod_inv2(ll a, ll m){return 1 < a ? m - mod_inv2(m % a, a) * m / a : 1;}