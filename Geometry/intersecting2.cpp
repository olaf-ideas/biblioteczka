#include <bits/stdc++.h>

using namespace std;

typedef long double T;
const T EPS = 1E-9;
inline bool isZero(const T &x) { return -EPS < x && x < EPS; }

struct P {
    T x, y;
    template<class U = T> P(U _x = U(0), U _y = U(0)) : x(T(_x)), y(T(_y)) { }
};

struct Line {
    P a, b;
    Line(const P &_a, const P &_b) : a(_a), b(_b) { }
};

inline T det(const P &a, const P &b, const P &c) { return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y); }
inline int ccw(const P &a, const P &b, const P &c) { T d = det(a, b, c); return (d > EPS) - (d < -EPS); }

struct Seg {
    P a, b;
    Seg(const P &_a, const P &_b) : a(_a), b(_b) { }
};

int intersect(const Line &p, const Line &q, P &ans) {
    T a1 = p.b.y - p.a.y;
    T b1 = p.a.x - p.b.x;
    T c1 = a1 * p.a.x + b1 * p.a.y;
    T a2 = q.b.y - q.a.y;
    T b2 = q.a.x - q.b.x;
    T c2 = a2 * q.a.x + b2 * q.a.y;
    T d = a1 * b2 - a2 * b1;
    if(isZero(d)) {
        if(fabs(a1 * p.a.x + b1 * p.a.y - c1 - a2 * p.a.x - b2 * p.a.y + c2) < EPS) return 2;
        return 0;
    }
    ans.x = (b2 * c1 - b1 * c2) / d;
    ans.y = (a1 * c2 - a2 * c1) / d;
    return 1;
}

int intersect(const Seg &p, const Seg &q, P &ans) {
    if(det(p.a, p.b, q.a) * det(p.a, p.b, q.b) < EPS && 
       det(q.a, q.b, p.a) * det(q.a, q.b, p.b) < EPS) return 0;
    return intersect(Line(p.a, p.b), Line(q.a, q.b), ans);        
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        int ans = 0;
        vector<Seg> segs;
        for(int i = 0; i < n; i++) {
            int x1, y1, x2, y2; scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            segs.push_back(Seg(P(x1, y1), P(x2, y2)));
            for(int j = 0; j < i; j++) {
                P res;
                ans += intersect(segs[i], segs[j], res);
            }
        }
        printf("%d\n", ans);
    }
}
