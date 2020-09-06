// olaf_surgut
//        _        __                             _   
//   ___ | | __ _ / _|  ___ _   _ _ __ __ _ _   _| |_ 
//  / _ \| |/ _` | |_  / __| | | | '__/ _` | | | | __|
// | (_) | | (_| |  _| \__ \ |_| | | | (_| | |_| | |_ 
//  \___/|_|\__,_|_|___|___/\__,_|_|  \__, |\__,_|\__|
//                |_____|             |___/           
//
#include <bits/stdc++.h>

using namespace std;

typedef long long int LL;
typedef long double LD;

const int INF = 1e9 + 7;
const LL LONG_INF = 1e18 + 7;
const LD EPS = 1e-9;

template <class T> inline T rd() {
    T r=0; int c = getchar();
    while(c < '0' || c > '9')   c = getchar();
    for(; '0' <= c && c <= '9'; c = getchar())
        r = (r << 3) + (r << 1) + c - 48;
    return r;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <class T> inline T rand(T l, T r) {
    return uniform_int_distribution<T>(l, r)(rng);
}

const int N = 1e6 + 7;

char s[N];
int p[N];

int main() {
    int q = rd<int>();
    while(q--) {
        int n = rd<int>(), b = rd<int>(), m = rd<int>();
        scanf("%s", s);
        
        int hs = 0;
        for(int i = 0; i < n; i++) {
            hs = int((hs * 1LL * b + s[i] - 'a' + 1) % m);
            s[i] = rand('a', 'z');
        }

        p[0] = 1;
        for(int i = 1; i < n; i++) {
            p[i] = int((p[i - 1] * 1LL * b) % m);
        }

        int ht1 = 0, ht2 = 0;
        for(int i = 0; i < n / 2; i++)  ht1 = int((ht1 * 1LL * b + s[i] - 'a' + 1) % m);
        for(int i = n / 2; i < n; i++)  ht2 = int((ht2 * 1LL * b + s[i] - 'a' + 1) % m);

        int ht = 0;
        for(int i = 0; i < n; i++)  ht = int((ht * 1LL * b + s[i] - 'a' + 1) % m);

        map<int, int> h1, h2;
        h1[ht1] = 0, h2[ht2] = 0;

        vector<pair<int, char>> changes;
        for(int i = 1; i <= 2e6; i++) {
            int id = rand(0, n - 1);
            char ch = rand('a', 'z');
            changes.push_back({id, s[id]});

            if(id < n / 2) {
                ht1 = int((ht1 + p[n / 2 - 1 - id] * 1LL * (ch - s[id])) % m + m) % m;
                h1[ht1] = i; 
            } else {
                ht2 = int((ht2 + p[n / 2 - 1 - (id - n / 2)] * 1LL * (ch - s[id])) % m + m) % m;
                h2[ht2] = i;
            }

            s[id] = ch;
        }

        pair<int, int> coll = {-1, -1};
        for(const pair<int, int>& h : h1) {
            ht1 = int((h.first * 1LL * p[n / 2]) % m);
            ht2 = (hs - ht1 + m) % m;

            if(h2.count(ht2)) {
                coll = {h.second, h2[ht2]};
                break;
            }
        }
        assert(coll != make_pair(-1, -1));

        for(int i = (int)changes.size() - 1; i >= min(coll.first, coll.second); i--) {
            if(coll.first <= i && changes[i].first < n / 2) {      
                s[changes[i].first] = changes[i].second;
            }

            if(coll.second <= i && changes[i].first >= n / 2) {
                s[changes[i].first] = changes[i].second;
            }
        }
        
        int h = 0;
        for(int i = 0; i < n; i++) {
            h = int((h * 1LL * b + s[i] - 'a' + 1) % m);
        }        
        
        assert(hs == h);
        printf("%s\n", s);
    }    
}

