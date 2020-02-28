#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool miller_rabin(ll a){
    
}

ll rho_polard(ll n){
    if(!(n&1))  return 2;
    //rand
    ll x, y, g = 1, a;
    x = rand()%n + 1, y = x, a = rand()%n+1;
    while(g == 1){
        x = ((x*x) + a) % n;
        y = ((y*y) + a) % n;
        y = ((y*y) + a) % n;
        g = __gcd(abs(x - y), n);
    }
    return g;
}

void factor(ll n, vector<ll>& r){
    if(n == 1)  return;
    if(miller_rabin(n)){
        r.push_back(n);
        return;
    }    
    ll f = rho_polard(n);
    factor(f, r);
    factor(n/f, r);
}

int main(){

}