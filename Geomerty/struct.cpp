#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const double PI = acos(-1.0);
const double INF = 1000000009;
double deg_to_rad (double x) {x * PI / 180.0;}
double rad_to_deg (double x) {x * 180.0 / PI;}

bool equal (const int x, const int y, const int eps = 0) {return abs(x-y) < eps;}
bool equal (const ll x, const ll y, const ll eps = 0) {return abs(x-y) < eps;}
bool equal (const double x, const double y, const double eps = 0.0000001) {return fabs(x-y) < eps;}
bool equal (const ld x, const ld y, const ld eps = 0.000000001) {return fabs(x-y) < eps;}

template <class T>
struct Point {
  T x, y;
  Point(T _x, T _y) : x(_x), y(_y) {}
  Point() : x(0), y(0) {}

  Point<int> operator +  (const Point<int> & p)   const {return Point<int>(x + p.x, y + p.y);}
  Point<int> operator *  (const Point<int> & p)   const {return Point<int>(x * p.x, y * p.y);}
  
  // distance from the other point
  ld         operator -  (const Point<ld> & p)    const {return hypotl(x - p.x, y - p.y);}
  ld         operator -  (const Point<ll> & p)    const {return hypotl(x - p.x, y - p.y);}
  double     operator -  (const Point<int> & p)   const {return hypot (x - p.x, y - p.y);}
  double     operator -  (const Point<double> &p) const {return hypot (x - p.x, y - p.y);}

  Point      operator += (const Point & p)        {x += p.x, y += p.y; return *this;}
  Point      operator *= (const Point & p)        {x *= p.x, y *= p.y; return *this;}

  template <class C>
  Point      operator +  (const C & v)            const {return Point<int>(x + v, y + v);}
  template <class C>
  Point      operator -  (const C & v)            const {return Point<int>(x - v, y - v);}
  template <class C>
  Point      operator *  (const C & v)            const {return Point<int>(x * v, y * v);}
  template <class C>
  Point      operator /  (const C & v)            const {return Point<int>(x / v, y / v);}

  template <class C>
  Point      operator += (const C & v)            {x += v, y += v; return *this;}
  template <class C>
  Point      operator -= (const C & v)            {x -= v, v -= v; return *this;}
  template <class C>
  Point      operator *= (const C & v)            {x *= v, y *= v; return *this;}
  template <class C>
  Point      operator /= (const C & v)            {x /= v, y /= v; return *this;}


  Point      operator =  (const Point & p)        {x = p.x, y = p.y; return *this;}

  bool       operator <  (const Point & p)        const {return x < p.x && y < p.y;}
  bool       operator == (const Point & p)        const {return equal(x, p.x) && equal(y, p.y);}
  bool       operator != (const Point & p)        const {return !equal(x, p.x) || !equal(y, p.y);}
};

template <class T>
struct Line {
  T a, b, c;
  Line (const T & _a, const T & _b, const T & _c) : a(_a), b(_b), c(_c) {}
  
  Line (const Point<T> & p1, const Point<T> & p2) {
    if (p1.x == p2.x)  a = 1., b = 0., c = -p1.x;
    else {
      a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
      b = 1.;
      c = -(double)(a * p1.x) - (b * p1.y);
    }
  }

  // distance from point
  ld       operator -  (const Point<ld> & p)    const {return fabs(a * p.x + b * p.y + c) / hypotl(a, b);}
  ld       operator -  (const Point<ll> & p)    const {return  abs(a * p.x + b * p.y + c) / hypotl(a, b);}
  double   operator -  (const Point<int> & p)   const {return  abs(a * p.x + b * p.y + c) / hypot (a, b);}
  double   operator -  (const Point<double> &p) const {return fabs(a * p.x + b * p.y + c) / hypot (a, b);}

  bool     operator |  (const Line & l)         const {return equal(a * l.b, b * l.a);}  // check if parallel
  bool     operator ^  (const Line & l)         const {return a * l.a == -1;}            // check if perpendicular

  Point<T> operator *  (const Line & l)         const {                                  // intersection point
    if(*this | l)  return Point<T>(INF,INF);
    Point<T> p;
    p.x = (l.b * c - b * l.c) / (a * l.b - l.a * b);
    if(equal(b, T(0)))  p.y = (l.c - l.a * p.x) / l.b;
    else                      p.y = (c - a * p.x) / b;
    if(p.y == -0) p.y = 0;
    return p;
  }

  bool     operator <  (const Line & l)         const {return b != l.b ? b < l.b : a != l.a ? a < l.a : c < l.c;}
  bool     operator == (const Line & l)         const {return equal(a, l.a) && equal(b, l.b) && equal(c, l.c);} 
};

template <class T>
struct Segment {
  Point<T> p, q;
  Segment (const Point<T> & _p, const Point<T> & _q) : q(_q), p(_p) {}

};

template <class T>
struct Vector {
  T x, y;
  Vector (const T & _x, const T & _y) : x(_x), y(_y) {}
  Vector (const Point<T> & p) : x(p.x), y(p.y) {}
  Vector (const Point<T> & p1, const Point<T> & p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}
};

template <class T>
struct Triangle {
  Point<T> a, b, c;
  vector<T> angles;
  Triangle (const Point<T> & _a, const Point<T> & _b, const Point<T> & _c) : a(_a), b(_b), c(_c), angles(3) {
    // calculate angles
  }
  T operator [] (int i) {assert(0 <= i && i <= 3);return angles[i];}
};

template <class T>
struct Rectangle {
  Point <T> p, q;
  Rectangle (const Point<T> & _p, const Point<T> & _q) : p(_p), q(_q) {} 
};

template <class T>
struct Circle {
  Point<T> p;
  T r;
  Circle (const Point<T> & _p, const T & _r) : p(_p), r(_r) {}
};

template <class T>
bool is_left(const Point<T> & a, const Point<T> & b, const Point<T> & c){

}

template <class T>
struct Polygon {
  multiset<Point<T>> points;

  Polygon () {}
  Polygon (const vector<Point<T>> & _points) {}
  Polygon (const multiset<Point<T>> & _points) {}
  Polygon (const set<Point<T>> & _points) {}

  void add (const Point<T> & p) {points.insert(p);}

  bool erase (const Point<T> & p) {points.erase(points.find(p));}

  size_t size () {return points.size();}

  vector<Point<T>> convex_hull () {
    vector<Point<T>> pts, h;
    pts.assign(points);
    for(int i = 0; i < 2; i++){
      auto start = h.size();
      for(const auto& p : pts){
        while(h.size() >= start+2 && is_left(h[h.size()-2], h[h.size()-1], p))
          h.pop_back();
        h.push_back(p);
      }
      h.pop_back();
      reverse(pts.begin(), pts.end());
    }
    return h;
  }

  template <class C> C cirsuit () {}
  template <class C> C area () {}
};

template <class T> ostream & operator << (ostream & o, const Point<T> & p) {o << p.x << ' ' << p.y; return o;}
template <class T> ostream & operator << (ostream & o, const Line<T> & l) {o << p.x << ' ' << p.y; return o;}
template <class T> ostream & operator << (ostream & o, const Segment<T> & s) {o << p.x << ' ' << p.y; return o;}
template <class T> ostream & operator << (ostream & o, const Vector<T> & v) {o << p.x << ' ' << p.y; return o;}
template <class T> ostream & operator << (ostream & o, const Triangle<T> & t) {o << p.x << ' ' << p.y; return o;}
template <class T> ostream & operator << (ostream & o, const Circle<T> & c) {o << p.x << ' ' << p.y; return o;}
template <class T> ostream & operator << (ostream & o, const Polygon<T> & p) {o << p.x << ' ' << p.y; return o;}


int main(){
  Point<int> a, b;
  Line<double> l1(1, 0, 0);
  Line<double> l2(1, -1, 1);
  Line<double> l3(Point<double>(0, 0), Point<double>(1, 1));
  Line<double> l4(Point<double>(0, 1), Point<double>(1, 0));

  cout << "l1: a = " << l1.a << " b = " << l1.b << " c = " << l1.c << "\n";
  cout << "l2: a = " << l2.a << " b = " << l2.b << " c = " << l2.c << "\n";
  cout << "l3: a = " << l3.a << " b = " << l3.b << " c = " << l3.c << "\n";
  cout << "l4: a = " << l4.a << " b = " << l4.b << " c = " << l4.c << "\n";
  cin >> a >> b;
  cout << (l1 - a) << '\n';
  cout << a << "\n" << b << "\n";
  // cout << fixed << setprecision(8) << dist(a,b) << "\n";
}

/* to do
template <class T>
struct Circle {
  Point<T> p;
  T r;
  Circle (const Point<T> & _p, const T & _r) : p(_p), r(_r) {}

  template <class C> C circuit () {}
  template <class C> C area () {}
};

template<class T>
struct Triangle {
  Point<T> p1, p2, p3;

  template <class C> C circuit () {return dist<T,C>(p1, p2) + dist<T,C>(p2, p3) + dist<T,C>(p3, p1);}
  template <class C> C area () {return abs((C(1) * p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y))/2);}
};

template <class T>
struct Rectangle {
  Point<T> p1, p2;

  template <class C> C circuit () {}
  template <class C> C area () {}
};
*/