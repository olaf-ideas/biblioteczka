#include <bits/stdc++.h>

using namespace std;

template <int MOD>
struct Modular {
    int value;
    static const int MOD_value = MOD;

    template <template T> Modular(T v = 0) { value = v % MOD; if(value < 0) value += MOD; }
    template <template T> Modular(T a, T b) : value(0) { *this += a; *this /= b; }

    Modular & operator += (const Modular &b) { value += b.value; if(value >= MOD) value -= MOD; return *this; }
    Modular & operator -= (const Modular &b) { value -= b.value; if(value < 0) value += MOD; return *this; }
    Modular & operator *= (const Modular &b) { value = (long long) value * b.value % MOD; return *this; }
    Modular & operator /= (const Modular &b) { return *this *= inverse(b); }   
 
    template <template T>
    friend Modular pot(Modular a, T e) {
        Modular res = 1;
        for(; e; a *= a, e >>= 1) if(e & 1) res *= a;
        return res;
    }
    friend Modular inverse(Modular a) { return pot(a, MOD - 2); }

    friend Modular operator + (Modular a, const Modular &b) { return a += b; }
    friend Modular operator - (Modular a, const Modular &b) { return a -= b; }
    friend Modular operator * (Modular a, const Modular &b) { return a *= b; }
    friend Modular operator / (Modular a, const Modular &b) { return a /= b; }
    friend ostream& operator << (ostream &os, const Modular &a) { return os << a.value; }
    friend bool operator == (const Modular &a, const Modular &b) { return a.value == b.value; }
    friend bool operator != (const Modular &a, const Modular &b) { return a.value != b.value; }
    friend Modular& operator ++ (Modular &a, int) { return a += 1; }
    friend Modular& operator ++ (const Modular &a, int) { return Modular(a)++; }
    friend Modular& operator -- (Modular &a, int) { return a -= 1; }
    friend Modular& operator -- (const Modular &a, int) { return Modular(a)--; }
    friend Modular operator - (const Modular &a) { return 0 - a; } 
};

typedef Mint = Modular<1000000007>;

int main() {

}
