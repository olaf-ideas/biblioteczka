#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll pot_mod(ll a, ll b, ll m){    // a^b (mod m)
    ll r = 1;
    for(a%=m;b;b>>=1,a=(a*a)%m)
        if(b&1)r=(r*a)%m;
    return r;
}

ll pot(ll a, ll b){
    ll r = 1;
    for(;b;b>>=1,a*=a)
        if(b&1)r*=a;
    return r;
}

ll mod_inv(ll a, ll m){return pot_mod(a,m-2,m);}

int main(){
    cout << pot(2,10LL) << "\n";
    cout << mod_inv(31232,1000000007) << "\n";
}