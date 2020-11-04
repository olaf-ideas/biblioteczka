// NAJWIEKSZY POLSKI HASHER
// autor: olaf_surgut
// zadanka: 
// Graffiti: https://solve.edu.pl/~sparingi/tasks/view/209

#include <bits/stdc++.h>

using namespace std;

template <int mod, int base>
struct MyHash {
    inline int add(int a, int b) const { a += b; return a < mod ? a : a - mod; }
    inline int sub(int a, int b) const { a -= b; return a < 0 ? a + mod : a; }
    inline int mul(int a, int b) const { return int((long long) a * b % mod); }
    inline int to_int(char c)    const { return int(c - 'a' + 1); }

    int n;
    vector<int> p, h;
    MyHash(const string &s) : n((int) s.size()), p(n, 1), h(n, n ? to_int(s[0]) : 0) {
        for(int i = 1; i < n; i++)  p[i] = mul(p[i - 1], base);
        for(int i = 1; i < n; i++)  h[i] = add(mul(h[i - 1], base), to_int(s[i]));
    }
    int operator () () const { return h[n - 1]; }
    int operator () (int l, int r) const {
        if(l == 0)  return h[r];
        return sub(h[r], mul(h[l - 1], p[r - l + 1]));
    }
};

template <int mod, int base>
int diff_pos(const MyHash<mod, base> &a, const MyHash<mod, base> &b) {
    int l = -1, r = min(a.n, b.n);
    while(r - l > 1) {
        int m = (l + r) >> 1;
        (a(0, m) == b(0, m) ? l : r) = m; 
    }
    return r;
}

typedef MyHash<1000000007, 31> Hash7;
typedef MyHash<1000000009, 31> Hash9;
typedef MyHash<1000000021, 31> Hash21;
typedef MyHash<1000000033, 31> Hash33;
typedef MyHash<1000000087, 31> Hash87;
typedef MyHash<1000000093, 31> Hash93;
typedef MyHash<1000000097, 31> Hash97;
