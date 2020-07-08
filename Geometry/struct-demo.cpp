#include <bits/stdc++.h>
using namespace std;

#define T double
#define EPS 0.000000001

inline bool isZero(T x){
  return -EPS <= x && x <= EPS;
}

inline T sgn(T x){
  return x < -EPS ? -1 : (x > EPS ? 1 : 0);
}

struct P { // punkt
  T x, y;
  P(T _x=0, T _y=0) : x(_x), y(_y) { }
};

struct L { // prosta
  P a, b;
  L(P _a, P _b) : a(_a), b(_b) { }
};

struct S { // odcinek
  P a, b;
  S(P _a, P _b) : a(_a), b(_b) { }
};

inline T skal(const P &a, const P &b, const P &c){  // kat miedzy wektorami
  return (b.x - a.x) * (c.x - a.x) * (b.y - a.y) * (c.y - a.y);
}
//      C
//     /
//    /--
//   / a \
//  A------B  wynik: a [-pi, +pi]

inline T dist(const P &a, const P &b){  // odleglosc pomiedzy a i b
  return sqrt(skal(a, b, b));
}

inline T dlrzut(const P &a, const P &b, const P &c){  // dlugosc rzutu wektora
  return skal(a, b, c) / dist(a, b);
}
//      C
//     /|
//    / |
//   /  |
//  A****-B  wynik: *

inline P rzut(const L &l, const P &c){  // rzut punktu na prosta
  T f = skal(l.a, l.b, c) / skal(l.a, l.b, l.b);
  return P(l.a.x + f * (l.b.x - l.a.x), l.a.y + f * (l.b.y - l.a.y));
}
//      C
//     /|
//    / |
//   /  |
//  A---D--B  wynik: D

inline T det(const P &a, const P &b, const P &c){ // iloczyn wektorowy
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline T strona(const P &a, const P &b, const P &c){  // po ktorej stronie jest punkt b
  return sgn(det(a, b, c));
}
//   B--C
//  / 
// A         wynik: -1 0 1 (lewo rownolegly prawo)

inline T pole(const P &a, const P &b, const P &c){  // pole trojkata
  return fabs(det(a, b, c)) / 2.;
}

inline T dist(const P &p, const L &l){  // odleglosc punktu od prostej
  return fabs(det(l.a, l.b, p)) / dist(l.a, l.b);
}

inline T dist(const P &p, const S &s){  // odleglosc punkty od odcinka
  if(skal(s.a, s.b, p) > 0 && skal(s.b, s.a, p) > 0)
    return dist(p, L(s.a, s.b));
  return min(dist(s.a, p), dist(s.b, p));
}

inline P symsr(const P &a, const P &b){ // symetria srodkowa
  return P(2 * a.x - b.x, 2 * a.y - b.y);
}
//      C
//     /
//    B
//   /
//  A        wynik: C 

inline P sympr(const L &l, const P &p){ // symertria osiowa
  return symsr(rzut(l, p), p);
}
// \ l
//  \  D 
//   \/
//   /\
//  P  \    wynik: D

inline S sym(const S &l){ // symetralna odcinka
  return S(P((l.a.x + l.b.x) / 2, (l.a.y + l.b.y) / 2),
           P((l.a.x + l.b.x) / 2 + (l.b.y - l.a.y), 
             (l.a.y + l.b.y) / 2 - (l.b.x - l.a.x)));
}
//    P 
//    |
// A-----B
//    |
//    Q     wynik: |PQ|

inline P obrot(const P &s, const P &p, T k){ // obrot o k stopni
  T cosk = cos(k), sink = sin(k);
  P v(p.x - s.x, p.y - s.y);
  return P(s.x + v.x * cosk - v.y * sink, 
           s.y + v.x * sink + v.y * cosk);
}
//        P
//       /
//      / \
//     S k |
//      \ /
//       \
//        Q  wynik: Q

inline T kat(const P &a, const P &b){
  return atan2(det(a, b), a * b);
}

inline bool on_segment(const P &p, const S &s){
  return min(s.a.x, s.b.x) <= p.x && p.x <= max(s.a.x, s.b.x) &&
         min(s.a.y, s.b.y) <= p.y && p.y <= max(s.a.y, s.b.y);
}

inline bool intersect(const S &s1, const S &s2) { // czy dwa odcinki sie przecinaja
  if(s1.a == s2.a || s1.a == s2.b || s1.b == s2.a || s1.b == s2.b) return true;
  long long d1 = det(s2.b-s2.a, s1.a-s2.a), d2 = det(s2.b-s2.a, s1.b-s2.a),
            d3 = det(s1.b-s1.a, s2.a-s1.a), d4 = det(s1.b-s1.a, s2.b-s1.a);
  return (d1 > 0 && d2 < 0 || d1 < 0 && d2 > 0) &&
         (d3 > 0 && d4 < 0 || d3 < 0 && d4 > 0) ||
          isZero(d1) && on_segment(s1.a, s2) ||
          isZero(d2) && on_segment(s1.b, s2) ||
          isZero(d3) && on_segment(s2.a, s1) ||
          isZero(d4) && on_segment(s2.b, s1);
}

inline P intersect_

int main(){

}
