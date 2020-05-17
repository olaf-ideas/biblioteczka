// nie wiem po co to zrobilem, ale chyba warto. (to przez Preiss'a) &copy 2020 Olaf Surgut
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const double PI = acosl(-1.0);
const double INF = 1000000009;
template <class T> T deg_to_rad (T x) {return x * PI / 180.0;}
template <class T> T rad_to_deg (T x) {return x * 180.0 / PI;}

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

// check if points are in counterclockwise order
template <class T>
bool ccw (const Point<T>& a, const Point<T> & b, const Point<T> & c){
	return (c.y - a.y) * (b.x - a.x) > (b.y - a.y) * (c.x - a.x);
}

template <class T>
struct Segment {
  Point<T> p, q;
  Segment (const Point<T> & _p, const Point<T> & _q) : q(_q), p(_p) {}
	
	T        operator () ()                     const {return p - q;}
	T        operator -  (const Segment<T> & s) const {return max({p - s.p, p - s.q, q - s.p, q - s.q});}
	T        operator -  (const Line<T> & l)    const {return max((l - p), (l - q));}
	T        operator -  (const Point<T> & t)   const {return max((p - t), (q - t));}
	
	
	// check if has intersection point
	bool     operator %  (const Segment<T> & s) const {return ccw(p, s.p, s.q) != ccw(q, s.p, s.q) && ccw(p, q, s.p) != ccw(p, q, s.q);}
	bool     operator %  (const Line<T> & l)    const {}
	
	// check if parallel
	bool     operator |  (const Segment<T> & s) const {return Line<T>(p, q) | Line<T>(s.p, s.q);}
	bool     operator |  (const Line<T> & l)    const {return Line<T>(p, q) | l;}
	
	// check if perpendicular
	bool     operator ^  (const Segment<T> & s) const {return Line<T>(p, q) ^ Line<T>(s.p, s.q);}
	bool     operator ^  (const Line<T> & l)    const {return Line<T>(p, q) ^ l;}
	
	// intersetion point
	Point<T> operator *  (const Segment<T> & s) const {}
	Point<T> operator *  (const Line<T> & l)    const {} 
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
  Point<T> p, q, t;
  vector<ld> angles;
  Triangle (const Point<T> & _p, const Point<T> & _q, const Point<T> & _t) : p(_p), q(_q), t(_t), angles(3) {
    ld a = p - q, b = q - t, c = t - p;
    angles[0] = acosl((a*a+b*b-c*c)/(2.0*a*b));
    angles[1] = acosl((b*b+c*c-a*a)/(2.0*b*c));
    angles[2] = acosl((a*a+c*c-b*b)/(2.0*a*c));
  }
  T operator [] (int i) const {assert(0 <= i && i <= 3); return angles[i];}
  T operator () () const {				// area of triangle
		T a = (p - q), b = (q - t), c = (t - p), s = (a + b + c)/2;
		return sqrt(s * (s - a) * (s - b) * (s - c)); 
	}
  T operator ~  () const {return (p - q) + (q - t) + (t - p);} // ciruit of trianlge

	T operator -  (const Triangle & t)    const {}
	T operator -  (const Point<T> & p)    const {}
	T operator -  (const Line<T> & l)     const {}
	T operator -  (const Segment<T> & s)  const {}
};

template <class T>
struct Rectangle {
	Point <T> p, q;
  Rectangle (const Point<T> & _p, const Point<T> & _q) : p(_p), q(_q) {} 
  T operator () () const {return abs(p.x - q.x) * abs(p.y - q.y);} // area of rectangle
  T operator ~  () const {return abs(p.x - q.x) * 2 + abs(p.y - q.y) * 2;} // ciruit of rectangle

	T operator -  (const Rectangle & r)    const {}
	T operator -  (const Point<T> & p)     const {}
	T operator -  (const Line<T> & l)      const {}
	T operator -  (const Segment<T> & s)   const {}
	T operator -  (const Triangle<T> & t)  const {}
};

template <class T>
struct Circle {
  Point<T> p;
  T r;
  Circle (const Point<T> & _p, const T & _r) : p(_p), r(_r) {}
  T operator () () const {} // area of circle
  T operator ~  () const {} // ciruit of circle

	T operator -  (const Circle & c)       const {}
	T operator -  (const Point<T> & p)     const {}
	T operator -  (const Line<T> & l)      const {}
	T operator -  (const Segment<T> & s)   const {}
	T operator -  (const Triangle<T> & t)  const {}
	T operator -  (const Rectangle<T> & r) const {}
};

template <class T>
struct Polygon {
  multiset<Point<T>> points;

  Polygon () {}
  Polygon (const vector<Point<T>> & _points) {}
  Polygon (const multiset<Point<T>> & _points) {}
  Polygon (const set<Point<T>> & _points) {}

  void add (const Point<T> & p) {points.insert(p);}

  void erase (const Point<T> & p) {points.erase(points.find(p));}

  size_t size () const {return points.size();}

  vector<Point<T>> convex_hull () {
    vector<Point<T>> pts, h;
    pts.assign(points);
    for(int i = 0; i < 2; i++){
      auto start = h.size();
      for(const auto& p : pts){
        while(h.size() >= start+2 && ccw(h[h.size()-2], h[h.size()-1], p))
          h.pop_back();
        h.push_back(p);
      }
      h.pop_back();
      reverse(pts.begin(), pts.end());
    }
    return h;
  }

  T operator () () const {} // area of polygon
  T operator ~  () const {} // ciruit of polygon
 
	T operator -  (const Polygon & p)      const {}
	T operator -  (const Point<T> & p)     const {}
	T operator -  (const Line<T> & l)      const {}
	T operator -  (const Segment<T> & s)   const {}
	T operator -  (const Triangle<T> & t)  const {}
	T operator -  (const Rectangle<T> & r) const {}
	T operator -  (const Circle<T> & c)    const {}
};

template <class T> ostream & operator << (ostream & o, const Point<T> & p) {o << p.x << ' ' << p.y; return o;}
template <class T> ostream & operator << (ostream & o, const Line<T> & l) {o << l.a << ' ' << l.b << ' ' << l.c; return o;}
template <class T> ostream & operator << (ostream & o, const Segment<T> & s) {o << s.p << ' ' << s.q; return o;}
template <class T> ostream & operator << (ostream & o, const Vector<T> & v) {o << v.x << ' ' << v.y; return o;}
template <class T> ostream & operator << (ostream & o, const Triangle<T> & t) {o << t.p << ' ' << t.q << ' ' << t.t; return o;}
template <class T> ostream & operator << (ostream & o, const Rectangle<T> & r) {o << r.p << ' ' << r.q; return o;}
template <class T> ostream & operator << (ostream & o, const Circle<T> & c) {o << c.p << ' ' << c.r; return o;}
template <class T> ostream & operator << (ostream & o, const Polygon<T> & p) {for(const Point<T> & x : p.points) o << x << ' '; return o;}

template <class T> istream & operator >> (istream & i, const Point<T> & p) {i >> p.x >> ' ' >> p.y; return i;}
template <class T> istream & operator >> (istream & i, const Line<T> & l) {i >> l.a >> l.b >> l.c; return i;}
template <class T> istream & operator >> (istream & i, const Segment<T> & s) {i >> s.p >> s.q; return i;}
template <class T> istream & operator >> (istream & i, const Vector<T> & v) {i >> v.x >> v.y; return i;}
template <class T> istream & operator >> (istream & i, const Triangle<T> & t) {i >> t.p >> t.q >> t.t; return i;}
template <class T> istream & operator >> (istream & i, const Rectangle<T> & r) {i >> r.p >> r.q; return i;}
template <class T> istream & operator >> (istream & i, const Circle<T> & c) {i >> c.p >> c.r; return i;}
template <class T> istream & operator >> (istream & i, const Polygon<T> & p) {for(Point<T> & x : p.points) i >> x; return i;}

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
  // cin >> a >> b;
  cout << (l1 - a) << '\n';
  cout << a << "\n" << b << "\n";
  // cout << fixed << setprecision(8) << dist(a,b) << "\n";
}

// &copy 2020 Olaf Surgut