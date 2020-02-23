#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll powmod(ll a, ll b, ll m){    // a^b (mod m)
    ll r = 1;
    a %= m;
    while(b){
        if(b&1) r = (r*a)%m;
        a = (a*a)%m;
        b >>= 1;
    }
    return r;
}

int main(){

}