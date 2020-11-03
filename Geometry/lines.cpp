#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld eps = 1E-9;

int sgn(ld v) { return (v > eps) - (v < -eps); }

struct P {
    ld x, y;
    P operator - (P other) { return P{x - other.x, y - other.y}; }
    P operator + (P other) { return P{x + other.x, y + other.y}; }
    ld operator * (P other) { return x * other.x + y * other.y; }
    ld operator ^ (P other) { return x * other.y - y * other.x; }
} none {LDBL_MAX, LDBL_MAX};

struct L {
    ld a, b, c;
    
    L(ld _a, ld _b, ld _c) : a(_a), b(_b), c(_c) { }
    L(P p, P q) {
        a = +(p.y - q.y);
        b = -(p.x - q.x);
        c = p ^ q;
    }

    P intersect(L l) {
        ld d = a * l.b - l.a * b;
        if(sgn(d) == 0) return none;
        ld x = -(c * l.b - l.c * b) / d;
        ld y = -(a * l.c - l.a * c) / d;
        return P{x, y};
    }
};

int main() {
    cout << fixed << setprecision(10) << none.x << '\n';
}
