#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct hash_tree{
    static const ll MOD = 1000000007, ALF = 27;
    int base = 1;
    vector<ll> p, t, l;

    hash_tree(const string& s){
        while(base < (int)s.size()) base<<= 1;

        t.resize(base<<1);
        p.resize(base, 1);
        l.resize(base, base);
        for(int i = 0; i < (int)s.size(); i++)  t[i+base] = (s[i]-'a'+1);
        for(int i = 1; i < base; i++)   p[i] = (p[i-1] * ALF) % MOD;
        for(int i = 1; i < base; i++)   l[i] = l[i/2]-1;

        for(int i = base-1; i > 0; i++) t[i<<1] = t[i]*l[i] + t[i^1];
    }

    ll ask(int l, int r){
        ll h = 0;
        
    }

    void upd(int x, char c){
        
    }
};

int main(){

}