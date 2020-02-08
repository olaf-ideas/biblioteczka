#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<ll,ll> extGcd(ll a, ll b){     // znajdz takie x,y ze ax + by = 1
    if(b == 0)  return {1LL, 0LL};
    auto p = extGcd(b, a%b);
    return {p.second, p.first-(a/b)*p.second};
}

ll modInv(ll a, ll m){              // znajdz x ze ax = 1 (mod m) oraz gcd(a,m) = 1
    pair<ll,ll> p = extGcd(a,m);
    if(p.first < 0) p.first += m;
    return p.first;
}

int main(){

}