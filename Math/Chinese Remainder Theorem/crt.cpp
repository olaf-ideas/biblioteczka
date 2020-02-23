// probably dont work
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<ll,ll> extGcd(ll a, ll b){     // znajdz takie x,y that ax + by = 1;
    if(b == 0)  return {1LL, 0LL};
    auto p = extGcd(b, a%b);
    return {p.second, p.first-(a/b)*p.second};
}

ll modInv(ll a, ll m){              // znajdz x ze ax = 1 (mod m) oraz gcd(a,m) = 1
    pair<ll,ll> p = extGcd(a,m);
    if(p.first < 0) p.first += m;
    return p.first;
}

ll crt(vector<ll> &a, vector<ll> &r){
    ll m = 1, res = 0;
    for(ll i = 0; i < (ll)a.size(); i++)    m *= a[i];    
    for(ll i = 0; i < (ll)a.size(); i++){
        ll mm = m/a[i];
        res += r[i] * modInv(mm, a[i]) * mm;
    }
    return res%m;
}

int t;

int main(){
    scanf("%d", &t);
    while(t--){
        ll a, n, b, m;
        scanf("%lld%lld%lld%lld", &a, &n, &b, &m);
        vector<ll> x = {a,b}, y = {n,m};
        printf("%lld\n", crt(x,y));
    }
}