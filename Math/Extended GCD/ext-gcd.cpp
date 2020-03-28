#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<ll,ll> ext_gcd(ll a, ll b){     // znajdz x,y takie ze ax + by = 1
    if(b == 0)  return {1LL, 0LL};
    auto p = ext_gcd(b, a%b);
    return {p.second, p.first-(a/b)*p.second};
}

ll mod_inv(ll a, ll m){              // znajdz x takie ze ax = 1 (mod m), warunki: gcd(a,m) = 1
    pair<ll,ll> p = ext_gcd(a,m);
    if(p.first < 0) p.first += m;
    return p.first;
}

ll mod_inv2(ll a, ll m){return 1<a?m-mod_inv2(m%a,a)*m/a:1;}

int main(){

}