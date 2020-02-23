// not done yet
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN = 4e6+6, BASE = 31, MOD = 1e9+7;

ll h[MAXN], pot[MAXN];

ll _h(int l, int r){
    return (((h[r]+MOD-h[l])%MOD)*pot[r-l+1])%MOD;
}

void calc_hash(string &s){
    const int n = (int)s.size();
    pot[0] = 1;
    for(int i = 1; i < n; i++)  pot[i] = (pot[i-1]*BASE) % MOD;

    for(int i = 0; i < n; i++)
        h[i+1] = (h[i] + (s[i]-'a'+1) * pot[i]) % MOD;
}

int main(){
    string a;
    cin >> a;
    calc_hash(a);
    int q;
    cin >> q;
    while(q--){
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        cout << _h(l1,r1) << " " << _h(l2,r2) << "\n";
    }
}
