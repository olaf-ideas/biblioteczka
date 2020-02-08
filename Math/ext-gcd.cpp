#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<ll,ll> extGcd(ll a, ll b){     // znajdz takie x,y ze ax + by = 1
    if(b == 0)  return {1LL, 0LL};
    auto p = extGcd(b, a%b);
    return {p.second, p.first-(a/b)*p.second};
}

int main(){

}