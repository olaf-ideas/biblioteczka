#include <bits/stdc++.h>

using namespace std;

typedef long long int LL;
typedef long double LD;

const LL LONG_INF = 1e18 + 7;
const int INF = 1e9 + 7;

const LD EPS = 1e-9;
const LD PI  = 3.141592653589793238;

#define ct const

inline bool isZero(LD x) { return -EPS <= x && x <= EPS; }

struct P {
    LD x, y;
    P(LD _x=0, LD _y=0) : x(_x), y(_y) { }
};

const P P_LONG_INT = P(LONG_INF, LONG_INF);
const P P_INF = P(INF, INF);
const P ANG = P(0, 1);
const P ORI = P(0, 0);

inline P  operator + (ct P& a, ct P& b) { return P(a.x + b.x, a.y + b.y); }
inline P  operator - (ct P& a, ct P& b) { return P(a.x - b.x, a.y - b.y); }
inline LD operator ^ (ct P& a, ct P& b) { return a.x * b.y - a.y * b.x; }
inline LD operator * (ct P& a, ct P& b) { return a.x * b.x + a.y * b.y; }

bool angleP(ct P& p) {
    return (ANG ^ p) > 0 || (ANG ^ p) == 0 && (ANG * p) > 0;
}

bool angle_compare(ct P& a, ct P& b) {
    return angleP(a) == angleP(b) && (a ^ b) > 0 || (angleP(a) && !angleP(b)); 
}

inline LD angle(ct P& p) { // return value between [0, 2 * PI]
    LD a = atan2(p.y, p.x);
    if(a < 0) a += 2. * PI;
    return a;
}

inline void a_sort(const vector<P>::iterator& b, const vector<P>::iterator& e) { sort(b, e, angle_compare); }

LD area(vector<P> p) {
    LD res = 0; int n = (int)p.size();
    a_sort(p.begin(), p.end());
    for(int i = 0; i < n; i++)  res += ((p[i] - ORI) ^ (p[(i + 1) % n] - ORI));
    return abs(res) / 2;
}

bool collinear(ct P& a, ct P& b, ct P& c) { return area({a, b, c}) == 0; }

P rotate(P p, P q, LD alpha) {
    LD cosi = cos(alpha), sini = sin(alpha);
    p = p - q;
    return P(cosi * p.x - sini * p.y, sini * p.x + cosi * p.y) + q;
}

struct L { // ax + b = y
    LD a, b;
    L(LD _a, LD _b) : a(_a), b(_b) { }
};

P intersection(ct L& a, ct L& b) {
    if(isZero(a.a - b.a))   return P_INF; // return P_LONG_INF;
    LD x = (b.b - a.b) / (a.a - b.a);
    return P(x, a.a * x + b.b);
}

LD dist(ct P& a, ct P& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline LD det(ct P& a, ct P& b, ct P& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

vector<P> convexHull(vector<P> p) {
  sort(p.begin(), p.end());
  vector<P> h;
  for(int i = 0; i < 2; i++) {
    auto start = h.size();
    for(const P& q : p) {
      while(h.size() >= start + 2 && det(h[h.size() - 2], h.back(), q) <= 0) // < points on edges
        h.pop_back();
      h.push_back(q);
    }
    h.pop_back();
    reverse(p.begin(), p.end());
  }
  return h;
}

// struct L {
//     P a, b;
//     L(P _a, P _b) : a(_a), b(_b) { }
// };

// struct S {
//     P a, b;
//     S(P _a, P _b) : a(_a), b(_b) { }
// };

// inline LD det(ct P& a, ct P& b, ct P& c) {
//     return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
// }

// inline LD dot(ct P& a, ct P& b, ct P& c) {
//     return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y);
// }

// inline LD dist(ct P& p, ct P& q) { // odleglosc punkt-punkt
//     return sqrt(dot(p, q, q));
// }

// inline LD dist(ct P& p, ct L& l) { // odleglosc punkt-prosta
//     return fabs(det(l.a, l.b, p)) / dist(l.a, l.b);
// }

// inline LD dist(ct P& p, ct S& s) { // odleglosc punkt-odcinek
//     if(dot(s.a, s.b, p) > 0 && dot(s.b, s.a, p) > 0)
//         return dist(p, L(s.a, s.b));
//     return min(dist(s.a, p), dist(s.b, p));
// }

// inline LD angle(ct P& p) { // return value between [0, 2 * PI]
//     LD a = atan2(p.y, p.x);
//     if(a < 0) a += 2. * PI;
//     return a;
// }

// inline void a_sort(ct vector<P>::iterator& b, ct vector<P>::iterator& e) {
//     sort(b, e, angleCMP);
// }

// inline LD area(ct P& a, ct P& b, ct P& c) { // pole trojkata
//     return fabs(det(a, b, c)) / 2;
// }

// inline LD area(vector<P> p) {
//     LD r = 0; int n = (int)p.size();
//     a_sort(p.begin(), p.end());
//     for(int i = 0; i < n; i++)
//         r = (())

//     return fabs(r) / 2;
// }

