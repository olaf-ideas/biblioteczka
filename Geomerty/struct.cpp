#include <bits/stdc++.h>
using namespace std;

template <class T> const T get_eps() {return is_floating_point<T>::value ? T(0.0000000001) : T(0);}

template <class T>
bool equal(const T & x, const T & y, const T eps = get_eps<T>()){
  if(is_integral<T>::value)        return abs(x-y) <= eps;
  if(is_floating_point<T>::value)  return fabs(x-y) <= eps;
  return x > y ? x - y <= eps : y - x <= eps;
}

template <class T>
struct Point {
  T x, y;
  Point(T _x, T _y) : x(_x), y(_y) {}
  Point():x(0),y(0){}

  Point operator +  (const Point & p) const {return Point(this->x + p.x, this->y + p.y);}
  Point operator -  (const Point & p) const {return Point(this->x - p.x, this->y - p.y);}
  Point operator *  (const Point & p) const {return Point(this->x * p.x, this->y * p.y);}
  Point operator /  (const Point & p) const {return Point(this->x / p.x, this->y / p.y);}

  Point operator += (const Point & p) {this->x += p.x, this->y += p.y; return *this;}
  Point operator -= (const Point & p) {this->x -= p.x, this->y -= p.y; return *this;}
  Point operator *= (const Point & p) {this->x *= p.x, this->y *= p.y; return *this;}
  Point operator /= (const Point & p) {this->x /= p.y, this->y /= p.y; return *this;}

  Point operator +  (const T & v)     const {return Point(this->x + v, this->y + v);}
  Point operator -  (const T & v)     const {return Point(this->x - v, this->y - v);}
  Point operator *  (const T & v)     const {return Point(this->x * v, this->y * v);}
  Point operator /  (const T & v)     const {return Point(this->x / v, this->y / v);}

  Point operator += (const T & v)     {this->x += v, this->y += v; return *this;}
  Point operator -= (const T & v)     {this->x -= v, this->y -= v; return *this;}
  Point operator *= (const T & v)     {this->x *= v, this->y *= v; return *this;}
  Point operator /= (const T & v)     {this->x /= v, this->y /= v; return *this;}

  Point operator =  (const Point & p) {this->x = p.x, this->y = p.y; return *this;}

  bool operator  <  (const Point & p) const {return this->x < p.x && this->y < p.y;}
  bool operator  == (const Point & p) const {return equal(this->x, p.x) && equal(this->y, p.y);}
  bool operator  != (const Point & p) const {return !equal(this->x, p.x) || !equal(this->y, p.y);}

  friend ostream & operator << (ostream & o, const Point<T> & p) {o << p.x << ' ' << p.y; return o;}
  friend istream & operator >> (istream & i, Point<T> & p) {i >> p.x >> p.y; return i;}
};

template <class T> T dot(const Point<T> & a) {return a.x * a.x + a.y * a.y;}
template <class T> T dist(const Point<T> & a, const Point<T> & b) {return dot(a - b);}  // sqrt after!!!

template <class T>
struct Line {
  T a, b, c;
  Line (const T & _a, const T & _b, const T & _c) : a(_a), b(_b), c(_c) {}
  Line (const Point<T> & p1, const Point<T> & p2){
    this->a = p1.y - p2.y;
    this->b = p2.x - p1.x;
    this->c = a * p1.x + b * p1.y; 
  }

  bool operator <  (const Line & l) const {return this->b != l.b ? this->b < l.b : this->a < l.a;}
  bool operator == (const Line & l) const {return equal(this->a, l.a) && equal(this->b, l.b) && equal(this->c, l.c);}
};

template<class T>
struct Segment {
  Point<T> p1, p2;
};

template<class T>
struct Circle {
  Point<T> p;
  T radius;
};

template<class T>
struct Triangle {
  Point<T> p1, p2, p3;
};

template<class T>
struct Square {
  Point<T> p1, p2;
};

template<class T>
struct Rectangle {
  Point<T> p1, p2;
};

int main(){
  Point<int> a, b;
  cin >> a >> b;
  cout << a << "\n" << b << "\n";
  cout << sqrt(dist(a,b)) << "\n";
}