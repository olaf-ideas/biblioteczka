#include <bits/stdc++.h>

using namespace std;

long long add(long long x, long long y, long long p) {
    return (x += y) < p ? x : x - p;
}

long long mul(long long x, long long y, long long p) {
    long long r = (long long)((long double)x * y - (long long)((long double)x * y / p + 0.5) * p);
    return r < 0 ? r + p : r;
}

long long pot(long long x, long long k, long long p) {
    long long r = 1 % p;
    for(; k > 0; k >>= 1, x = mul(x, x, p))
        if(k & 1)   r = mul(r, x, p);
    return r;
}

bool miller_rabin(long long n) {
    if(n == 2)  return true;
    if(n < 2 || !(n & 1))   return false;
    long long s = 0, r = n - 1;
    for(; !(r & 1); r >>= 1, s++);
    for(int p : {2, 3, 5, 7, 11, 13, 17, 19, 23}) {
        long long c = pot(p, r, n), x;
        for(int j = 0; j < s; j++) {
            x = mul(c, c, n);
            if(x == 1 && c != 1 && c != n - 1)  return false;
        }
        if(c != 1)  return false;
    }
    return true;
}

long long gcd(long long a, long long b) {
    int s = 0;
    while(a) {
        for(; !(a & 1) && !(b & 1); s++, a >>= 1, b >>= 1);
        for(; !(a & 1); a >>= 1);
        for(; !(b & 1); b >>= 1);
        if(a < b)   swap(a, b);
        a -= b;
    }
    return b << s;
}

long long c = 1;
long long rho(long long x, long long n) { 
    return add(mul(x, x, n), c, n); 
}

long long pollard(long long n) {
    long long x = 2, y = 2, d = 1;
    while(d == 1) {
        x = rho(x, n), y = rho(rho(y, n), n);
        d = __gcd(abs(x - y), n);
    }
    if(d == n)  return -1;
    return d;
}

vector<long long> slow_factor(long long n) {
    vector<long long> f;
    for(long long i = 2; i * i <= n; i++) {
        while(n % i == 0) {
            f.push_back(i);
            n /= i;
        }
    }
    if(n > 1)   f.push_back(n);
    return f;
}

vector<long long> factor(long long n) {
    if(miller_rabin(n)) return vector<long long>({n});
    if(n < 100)         return slow_factor(n);
    
    long long d = pollard(n);
    assert(d != -1);
    vector<long long> f1 = factor(d);
    vector<long long> f2 = factor(n / d);
    f1.insert(f1.end(), f2.begin(), f2.end());
    return f1;
}

int main() {
    long long n; cin >> n;
    vector<long long> f = factor(n);
    for(long long x : f)    cout << x << ' ';
    cout << '\n';
}
