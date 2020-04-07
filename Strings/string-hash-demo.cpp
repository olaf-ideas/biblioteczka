#include <bits/stdc++.h>
#define sz(x) (int)(x.size())
using namespace std;
typedef long long ll;
const ll MAXN = 4e6+6, BASE = 31, MOD = 1e9+7;

ll h[MAXN], p[MAXN];

ll _h(int l, int r){
    return ((h[r] - h[l-1]*p[r-l+1]) % MOD + MOD) % MOD;
}

void calc_hash(const string &s){
    p[0] = 1;
    for(int i = 1; i < sz(s); i++)  p[i] = (p[i-1]*BASE)%MOD;

    h[0] = s[0] - 'a' + 1;
    for(int i = 1; i < sz(s); i++)
        h[i] = (h[i-1]*BASE + s[i] - 'a' + 1) % MOD;
}

template<int BASE = 26, int MOD1 = 1000000007, int MOD2 = 1000000009>
struct Hash{
    vector<int> p1, p2, h1, h2;

    Hash(const string& s){
        p1.resize(sz(s), 1), p2.resize(sz(s));
        h1.resize(sz(s), s[0]-'a'+1), h2.resize(sz(s), s[0]-'a'+1);
        for(int i = 1; i < sz(s); i++)  p1[i] = (p1[i-1] * BASE) % MOD1;
        for(int i = 1; i < sz(s); i++)  h1[i] = (h1[i-1] * BASE + s[i] - 'a' + 1) % MOD1;
        for(int i = 1; i < sz(s); i++)  p2[i] = (p2[i-1] * BASE) % MOD2;
        for(int i = 1; i < sz(s); i++)  h2[i] = (h2[i-1] * BASE + s[i] - 'a' + 1) % MOD2;
    }

    pair<int,int> h(int l, int r){
        return make_pair(((h1[r] - h1[l-1] * p1[r-l+1]) % MOD1 + MOD1) % MOD1, 
                         ((h2[r] - h2[l-1] * p2[r-l+1]) % MOD2 + MOD2) % MOD2);
    }
};

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
