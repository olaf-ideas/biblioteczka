#include <bits/stdc++.h>

using namespace std;

typedef long double LD;

typedef long double T;

const LD EPS = 1e-9;

inline bool is_zero(LD value) { return -EPS <= value && value <= EPS; }

const LD PI = acos(-1);

struct P {
  T x, y;
  P(T _x = 0, T _y = 0) : x(_x), y(_y) { }
  inline P operator + (const P &other) const { return P(x + other.x, y + other.y); }
  inline P operator - (const P &other) const { return P(x - other.x, y - other.y); }

  inline T operator * (const P &other) const { return x * other.x + y * other.y; }  // dot
  inline T operator ^ (const P &other) const { return x * other.y - y * other.x; }  // det

  P operator * (const T value) const { return P(x * value, y * value); }
  P operator / (const T value) const { return P(x / value, y / value); }

  bool operator == (const P &other) const { return is_zero(x - other.x) && is_zero(y - other.y); }
  bool operator != (const P &other) const { return !(*this == other); }

  void read() { cin >> x >> y; }
};

P perp(const P &p) { return P(-p.y, p.x); }

LD abs(const P &p) { return sqrtl(p * p); }
LD dist(const P &p, const P &q) { return abs(p - q); }
LD angle(const P &p, const P &q) { return acosl(max(-1.L, min(1.L, (p * q) / abs(p) / abs(q)))); }
LD angle(const P &p) { return atan2l(p.y, p.x); } // [-pi, pi]

bool is_perp(const P &p, const P &q) { return is_zero(p * q); }

T det(const P &p, const P &q, const P &w) { return (q - p) ^ (w - p); }

struct Line {
  P v; T c;
  Line(const P &_v, T _c) : v(_v), c(_c) { }
  Line(T _a, T _b, T _c) : v(_b, -_a), c(_c) { }
  Line(const P &_p, const P &_q) : v(_q - _p), c(v ^ _p) {  }
  T side(const P &p) const { return (v ^ p) - c; }
  LD dist(const P &p) const { return abs(side(p)) / abs(v); }
  Line perpThrough(const P &p) const { return Line(p, p + perp(v)); }
  bool operator == (const Line &l) const {
    if(is_zero(v.x) && is_zero(l.v.x))  return true;
    if(is_zero(v.x) != is_zero(l.v.x))  return false;
    LD d = l.v.x / v.x;
    return is_zero(v.x * d - l.v.x) && is_zero(v.y * d - l.v.y) && is_zero(c * d - l.c);
  }
};

bool inter(const Line &a, const Line &b, P &out) {
  LD d = a.v ^ b.v;
  if(is_zero(d))  return false;
  return out = (b.v * a.c - a.v * b.c) / d, true;
}

struct Seg {
  P p, q;
  Seg(const P& _p, const P& _q) : p(_p), q(_q) { }
  
  bool operator == (const Seg &other) const { return (p == other.p && q == other.q) || (q == other.p && p == other.q); }
};

bool inter(const Seg &a, const Seg &b, P &out) {
  if(det(a.p, a.q, b.p) * det(a.p, a.q, b.q) < EPS ||
     det(b.p, b.q, a.p) * det(b.p, b.q, a.q) < EPS) return false;
  return inter(Line(a.p, a.q), Line(b.p, b.q), out);
}

bool inter(const Seg &a, const Seg &b) {
  P out;
  if(!inter(Line(a.p, a.q), Line(b.p, b.q), out)) return false;
  return is_zero(dist(a.p, out) + dist(a.q, out) - dist(a.p, a.q));
}

int main() {
  ios::sync_with_stdio(0), cin.tie(nullptr);
  while(true) {
    int n; cin >> n;
    if(n == 0)  return 0;
    vector<P> p(n);
    for(int i = 0; i < n; i++) {
      p[i].read();
    }
    bool ok = true;
    for(int i = 0; i < n - 1; i++) {
      for(int j = i + 1; j < n - 1; j++) {
        if(inter(Seg(p[i], p[i + 1]), Seg(p[j], p[j + 1]))){
          ok = false;
        }
        if(!ok) break;
      }
      if(inter(Seg(p[i], p[i + 1]), Seg(p[n - 1], p[0]))) {
        ok = false;
      }
      if(!ok) break;
    }
    if(ok)  cout << "YES\n";
    else    cout << "NO\n";
  }
}
