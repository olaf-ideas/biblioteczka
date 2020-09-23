#include <bits/stdc++.h>

using namespace std;

namespace math {
    template <typename T>
    T mul(T a, T b, T mod) {
        // return (__int128(a) * b) % mod;
        if(mod < INT_MAX)   return (long long) a * b % mod;
        T res = 0;
        for(a %= mod, b %= mod; b; b >>= 1, a = (a + a) % mod)
            if(b & 1)   res = (res + a) % mod;
        return res;
    }

    template <typename T>
    T pot(T a, T b, T mod) {
        T res = 1;
        for(a %= mod; b; b >>= 1, a = mul(a, a, mod))
            if(b & 1)   res = mul(res, a, mod);
        return res;
    }

    template <typename T>
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
    }
    return true;
};

namespace primes {
    typedef long long LL;

    LL mul(LL a, LL b, LL mod) {
    //    return (__int128(a) * b) % mod;
        LL res = 0;
        for(a %= mod, b %= mod; b; b >>= 1, a = (a + a) % mod)
            if(b & 1)   res = (res + a) % mod;
        return res;
    }

    LL pot(LL a, LL b, LL mod) {
        LL res = 1;
        for(a %= mod; b; b >>= 1, a = mul(a, a, mod))
            if(b & 1)   res = mul(res, a, mod);
        return res;
    }

    bool test(LL n) {
        if(n == 2)  return true;
        if(n < 2 || !(n & 1))   return false;
        
        LL d = n - 1;
        LL s = 0;
        for(; !(d & 1); d >>= 1, s++);
        
        for(LL i : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) if(i % n) {
            LL x = pot(i, d, n);
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

    LL gcd(LL a, LL b) { return a ? gcd(b % a, a) : b; }

    LL rho(LL x, LL mod, LL c) { 
        LL y = mul(x, x, mod) + c;
        return y < mod ? y : y - mod;    
    }

    void pollard(LL n, vector<LL> &f) {
        if(n <= 1)  return;
        if(test(n)) {
            f.push_back(n);
            return;
        }
        
        for(LL c = 1; ; c++) {
            LL x = 2, y = 2, d = 1;
            while(d == 1) {
                x = rho(x, n, c);
                y = rho(rho(y, n, c), n, c);
                d = gcd(abs(x - y), n);
            }
            if(d < n) {
                pollard(d, f);
                pollard(n / d, f);
                return;
            }
        }
    }

    // average 0.003s per query
    void factor(LL n, vector<LL> &f) {
        for(int i = 2; i < 100; i++) while(n % i == 0)
            n /= i, f.push_back(i);

        pollard(n, f);
        sort(f.begin(), f.end());
    }
} // primes
