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

int n, b, m;
char s[N];

int p[N];

int mul(int x, int y) { return int((x * 1LL * y) % m); }
int add(int x, int y) { return (x + y) % m; }
int sub(int x, int y) { return (x - y + m) % m; }

int main() {
    n = rd<int>(), b = rd<int>(), m = rd<int>();
    scanf("%s", s);
    
    p[0] = 1;
    for(int i = 1; i < n; i++)  p[i] = mul(p[i - 1], b); 

    int ans = 0;
    for(int i = 0; i < n; i++)  ans = add(mul(ans, b), s[i] - 'a' + 1);

    for(int i = 0; i < n; i++)  s[i] = rand<char>('a', 'z');

    int left_hasz, right_hasz = 0;
    for(int i = 0; i < n / 2; i++)  left_hasz = add(mul(left_hasz, b), s[i] - 'a' + 1);
    for(int i = n / 2; i < n; i++)  right_hasz = add(mul(right_hasz, b), s[i] - 'a' + 1);


    vector<pair<int, int>> right = {{right_hasz, 0}};
    vector<pair<int, char>> change;
    for(int rep = 1; rep < 1e6; rep++) {
        int id = rand<int>(n / 2, n);
        char ch = rand<char>('a', 'z');

        right_hasz = add(right_hasz, mul(p[n / 2 - 1 - (id - n / 2)], sub(ch, s[id])));
        s[id] = ch;
            
        change.push_back({id, ch});
    }



    vector<pair<int, int>> left = {{left_hasz, 0}};
    for(int rep = 1; rep < 1e6; rep++) {
        int id = rand<int>(0, n / 2 - 1);
        char ch = rand<char>('a', 'z');
        left_hasz = add(left_hasz,  mul(p[n / 2 - 1 - id], sub(ch, s[id])));
        left.push_back({left_hasz, rep});
    }
    sort(left.begin(), left.end());

82         pair<int, int> coll = {-1, -1};
 83         for(const pair<int, int>& h : h1) {
 84             ht1 = int((h.first * 1LL * p[n / 2]) % m);
 85             ht2 = (hs - ht1 + m) % m;
 86 
 87             auto it = lower_bound(h2.begin(), h2.end(), make_pair(ht2, -1));
 88             if(it != h2.end() && it->first == ht2) {
 89                 coll = {h.second, it->second};
 90                 break;
 91             }
 92         }
 93         assert(coll != make_pair(-1, -1));


    for(int rep = 1; rep < 1e6; rep++) {    
        int id = rand<int>(n / 2, n);
        char ch = rand<char>('a', 'z');
        right_hasz = add(right_hasz, mul(p[n / 2 - 1 - (id - n / 2)], sub(ch, s[id])));
 

        
        int left_res_hasz = mul(
        ht1 = int((h.first * 1LL * p[n / 2]) % m);       
    }
}

















