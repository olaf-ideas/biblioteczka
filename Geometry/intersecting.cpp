#include <bits/stdc++.h>

using namespace std;

typedef long double T;
const T EPS = 1E-9;
bool isZero(const T &d) { return -EPS < d && d < EPS; }
 
struct P {
    T x, y;
    P operator + (const P &p) const { return {x + p.x, y + p.y}; }
    P operator - (const P &p) const { return {x - p.x, y - p.y}; }
    P operator * (const T &d) const { return {x * d, y * d}; }
    P operator / (const T &d) const { return {x / d, y / d}; }
};

bool operator == (const P &a, const P &b) { return isZero(a.x - b.x) && isZero(a.y - b.y); }
bool operator != (const P &a, const P &b) { return !(a == b); }

T sq(const P &p) { return p.x * p.x + p.y * p.y; }
long double abs(const P &p) { return sqrt(sq(p)); }
int sgn(const T &d) { return (T(0) < d) - (d < T(0)); }
P translate(const P &v, const P &p) { return p + v; }
P scale(const P &c, long double factor, const P &p) { return c + (p - c) * factor; }
P rotate(const P &p, long double a) { return {p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a)}; }
P perp(const P &p) { return {-p.y, p.x}; }
T dot(const P &v, const P &w) { return v.x * w.x + v.y * w.y; }
bool isPerp(const P &v, const P &w) { return dot(v, w) == 0; }
long double angle(const P &v, const P &w) { return acos(max(-1.0L, min(1.0L, dot(v, w) / abs(v) / abs(w)))); }
T cross(const P &v, const P &w) { return v.x * w.y - v.y * w.x; }
T orient(const P &a, const P &b, const P &c) { return cross(b - a, c - a); }

struct Line {
    P v; T c;
    Line(const P &_v, const T &_c) : v(_v), c(_c) { }
    Line(const T &a, const T &b, const T &_c) : v({b, -a}), c(_c) { }
    Line(const P &p, const P &q) : v(q - p), c(cross(v, p)) { } 
    T side(const P &p) const { return cross(v, p) - c; }
    long double dist(const P &p) const { return abs(side(p)) / abs(v); }
    long double sqDist(const P &p) const { return side(p) * side(p) / (long double) sq(v); }
    Line perpThrough(const P &p) const { return {p, p + perp(v)}; }
    bool operator == (const Line &l) const { 
        if(isZero(v.x) && isZero(l.v.x)) return true;
        long double d = l.v.x / v.x;
        return isZero(v.x * d - l.v.x) && isZero(v.y * d - l.v.y) && isZero(c * d - l.c);
    }
};
bool inter(const Line &a, const Line &b, P &out) {
    T d = cross(a.v, b.v);
    if(isZero(d))  return false;
    out = (b.v * a.c - a.v * b.c) / d;
    return true;
}


int main() {
    int n; scanf("%d", &n);
    puts("INTERSECTING LINES OUTPUT");
    while(n--) {
        int x1, y1, x2, y2, x3, y3, x4, y4;
        scanf("%d %d %d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
        Line a(P{x1, y1}, P{x2, y2});
        Line b(P{x3, y3}, P{x4, y4});
    
        // printf("%Lf %Lf %Lf %Lf %Lf %Lf ", a.v.x, a.v.y, a.c, b.v.x, b.v.y, b.c);   
 
        if(a == b) {
            puts("LINE");
            continue;
        }
            P p;
        if(inter(a, b, p)) {
            printf("POINT %.2Lf %.2LF\n", p.x, p.y); 
        } else {
            printf("NONE\n");
        }
    }
    puts("END OF OUTPUT");
}
