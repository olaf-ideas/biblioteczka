#include <bits/stdc++.h>

using namespace std;

namespace math {
    template <typename T> // tested
    T gcd(T a, T b) { return a ? gcd(b % a, a) : b; }
    template <typename T> // tested
    T lcm(T a, T b) { return a / gcd(a, b) * b; }
    template <typename T> // tested
    void ext_gcd(T &x, T &y, T a, T b) {
        if(!a)  { x = 0, y = 1; return; }
        ext_gcd(y, x, b % a, a);
        x -= y * (b / a);
    }
    template <typename T> // tested
    T inv(T a, T mod) {
        assert(gcd(a, mod) == 1);
        T x, y; ext_gcd(x, y, a, mod);
        return x < 0 ? x + mod : x;
    }
    template <typename T> // tested
    T add(T a, T b, T mod) { a += b; return a < mod ? a : a - mod; }
    template <typename T> // tested
    T sub(T a, T b, T mod) { a -= b; return a < 0 ? a + mod : a; }
    template <typename T> // tested
    T mul(T a, T b, T mod) {
        if(a >= mod)  a %= mod;
        if(b >= mod)  b %= mod;
#ifndef LOCAL // overflows
        long long c = (long double)(a) * b / mod;
        long long r = a * b - c * mod;
        return r < 0 ? r % mod + mod : r % mod;
#else
        T res = 0;
        for(; b; a = add(a, a, mod), b >>= 1)
            if(b & 1)   res = add(a, res, mod);
        return res;
#endif
    }

    template <typename T> // tested
    T div(T a, T b, T mod) { return mul(a, inv(b, mod), mod); }
    template <typename T> // tested
    T pot(T a, T b, T mod) {
        T res = 1;
        for(a %= mod; b; b >>= 1, a = mul(a, a, mod))
            if(b & 1)   res = mul(res, a, mod);
        return res;
    }

    template <typename T> // tested
    vector<T> primes(T n) {
        assert(n <= T(100000000));
        vector<int> s(n / 32 + 1);
        for(T i = 2; i * i <= n; i++) {
            if(!(s[i >> 5] & (1 << (i & 31))))
                for(T j = i * i; j <= n; j += i)
                    s[j >> 5] |= (1 << (j & 31));
        }
        vector<T> p;
        for(T i = 2; i <= n; i++)
            if(!(s[i >> 5] & (1 << (i & 31))))
                p.push_back(i);
        return p;
    }

    template <typename T> // tested
    bool is_prime(T n) {
        if(n == 2)  return true;
        if(n < 2 || !(n & 1))   return false;
        
        T d = n - 1, s = 0;
        for(; !(d & 1); d >>= 1, s++);

        for(T i : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) if(i % n) {
            T x = pot(i, d, n);
            if(x != 1) {
                bool c = true;
                for(int j = 0; j < s; j++) {
                    if(x == n - 1) {
                        c = false;
                        break;
                    }
                    x = mul(x, x, n);
                }
                if(c)   return false;
            }
        }
        return true;
    }

    template <typename T> // tested
    void pollard(T n, vector<T> &f) {
        if(n <= 1)  return;
        if(is_prime(n)) {
            f.push_back(n);
            return;
        }
        auto rho = [&] (T x, T mod, T c) { T y = mul(x, x, mod) + c; return y < mod ? y : y - mod; };
        for(T c = 1; ; c++) {
            T x = 2, y = 2, d = 1;
            while(d == 1) {
                x = rho(x, n, c);
                y = rho(rho(y, n, c), n, c);
                d = gcd((x < y ? y - x : x - y), n);
            }
            if(d < n) {
                pollard(d, f);
                pollard(n / d, f);
                return;
            }
        }
    }

    // average 0.003s per query
    template <typename T> // tested
    vector<T> factor(T n) {
        vector<T> f;
        for(int i = 2; i < 100; i++) while(n % i == 0)
            n /= i, f.push_back(i);
        pollard(n, f);
        sort(f.begin(), f.end());
        return f;
    }

    template <typename T> // tested
    vector<pair<T, int>> factor_compress(const vector<T> &f) {
        vector<pair<T, int>> res;
        res.emplace_back(f[0], 0);
        for(auto x : f) {
            if(res.back().first != x)   res.emplace_back(x, 0);
            res.back().second++;
        }
        return res;
    }

    template <typename T> // tested
    vector<T> divisors(const vector<T> &ff) {
        const auto f = factor_compress(ff);
        vector<T> d;
        function<void(int, int, T)> gen = [&](int i, int k, T dd) {
            if(i == (int) f.size()) d.push_back(dd);
            else {
                if(k < f[i].second) gen(i, k + 1, dd * f[i].first);
                gen(i + 1, 0, dd);   
            }
        };
        gen(0, 0, 1);
        sort(d.begin(), d.end());
        return d;
    }

    template <typename T> // tested
    vector<T> divisors(T n) {
        return divisors(factor(n));
    }
} // math

const long long ten = 1e18L;

long long r() {
    return (rand() | ((long long) rand() << 32LL)) % ten;
}

int main() {
    for(int rep = 0; rep < 100000; rep++) {
        long long n = r();
        vector<long long> f = math::factor(n);
        cout << n << ": ";
        for(auto x : f) cout << x << ' ';
        if(f.size() == 1)   cout << "PRIME";
        cout << '\n';
    }
}
