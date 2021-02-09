#include <set>

namespace geo {

template <typename T>
struct TPoint {
	T x;
	T y;
	int id;
	
	TPoint() : x(0), y(0), id(-1) { }
	TPoint(const T &_x, const T &_y) : x(_x), y(_y), id(-1) { }
	TPoint(const T &_x, const T &_y, int _id) : x(_x), y(_y), id(_id) { }
	
	static constexpr T eps = static_cast<T>(1e-9);
	
	inline TPoint operator + (const TPoint &other) const { return TPoint(x + other.x, y + other.y); }
	inline TPoint operator - (const TPoint &other) const { return TPoint(x - other.x, y - other.y); }
	inline TPoint operator - () const { return TPoint(-x, -y); }
	
	inline TPoint operator * (const T &value) const { return TPoint(x * value, y * value); }
	inline TPoint operator / (const T &value) const { return TPoint(x / value, y / value); }
	
	// iloczyn wektorowy
	inline T operator * (const TPoint &other) const { return x * other.y - y * other.x; }
	
	// iloczyn skalarny
	inline T operator ^ (const TPoint &other) const { return x * other.x + y * other.y; }
	
	static inline bool equal(const T &a, const T &b) {
		return -eps <= a - b && a - b <= +eps;
	}
	
	static inline bool less(const T &a, const T &b) {
		return a - b < -eps;
	}
	
	inline bool operator < (const TPoint &other) const {
		return (less(x, other.x) || (equal(x, other.x) && less(y, other.y)));
	}
	
	inline bool operator == (const TPoint &other) const {
		return equal(x, other.x) && equal(y, other.y);
	}
	
	// czy punkt nad osią x, lub na prawo od (0,0)
	inline bool is_above() const {
		return (y > eps || (equal(y, 0) && x > eps));
	}
	
	// moduł wektora
	inline long double abs() const {
		return sqrtl((long double) x * x + (long double) y * y);
	}
	
	friend inline long double angle(const TPoint &a, const TPoint &b) {
		return acos(max(-1.l, min(1.l, (a ^ b) / abs(a) / abs(b))));
	}
	
	// kradrat modułu wektora
	inline T abs2() const {
		return x * x + y * y;
	}
	
	// iloczyn wektorowy, a - środek
	// < 0  -> c na prawo od b
	// == 0 -> b i c równoległe
	// > 0  -> c na lewo od b
	friend inline T det(const TPoint &a, const TPoint &b, const TPoint &c) {
		return (b - a) * (c - a);
	}
	
	friend inline std::istream& operator >> (std::istream &is, TPoint &p) {
		return is >> p.x >> p.y;
	}
	
	friend inline std::ostream& operator << (std::ostream &os, const TPoint &p) {
		return os << p.x << ' ' << p.y;
	}
};

template <typename T> inline typename std::enable_if<std::is_floating_point<T>::value, TPoint<T>>::type rotate(const TPoint<T> &p, const T &angle) {
	T c = cos(angle), s = sin(angle);
	return P(p.x * c - p.y * s, p.x * s + p.y * c);
}

// scaled by angle length
template <typename T> inline typename std::enable_if<std::is_integral<T>::value, TPoint<T>>::type rotate(const TPoint<T> &p, const TPoint<T> &angle) {
	return P(p * angle, p ^ angle);
}

template <typename T>
inline int sgn(const T &v) {
	return (v > static_cast<T>(1e-9)) - (v < static_cast<T>(-1e-9));
}

// sprawdz czy punkt p jest w kółku a, b z średnica dist(a, b)
template <typename T>
inline bool in_disk(const TPoint<T> &a, const TPoint<T> &b, const TPoint<T> &p) {
	return (a - p) ^ (b - p);
}

template <typename T>
inline bool on_segment(const TPoint<T> &a, const TPoint<T> &b, const TPoint<T> &p) {
	return sgn(det(a, b, p)) == 0 && in_disk(a, b, p);
}

template <typename T>
struct TSegment {
	TPoint<T> p;
	TPoint<T> q;
	int id;
	
	TSegment() : p(), q(), id(-1) { }
	TSegment(const TPoint<T> &_p, const TPoint<T> &_q) : p(_p), q(_q), id(-1) { }
	TSegment(const TPoint<T> &_p, const TPoint<T> &_q, int _id) : p(_p), q(_q), id(_id) { }
};

// tylko jeden punkt, bez końców odcinka
template <typename T>
inline bool proper_inter(const TSegment<T> &a, const TSegment<T> &b, TPoint<long double> &res) {
	T e = det(a.p, a.q, b.p), t = det(a.p, a.q, b.q);
	T z = det(b.p, b.q, a.p), w = det(b.p, b.q, a.q);
	if(sgn(e) * sgn(t) < 0 && sgn(z) * sgn(w) < 0) {
		res = ((a.p * w) - (a.q * z)) / (w - z); 
		return true;
	}
	return false;
}

template <typename T>
inline std::set<TPoint<long double>> inter(const TSegment<T> &a, const TSegment<T> &b) {
	TPoint<long double> res;
	if(proper_inter(a, b, res))	return {res};
	std::set<TPoint<long double>> s;
	if(on_segment(a.p, a.q, b.p))	s.insert(TPoint<long double>(b.p));
	if(on_segment(a.p, a.q, b.q))	s.insert(TPoint<long double>(b.q));
	if(on_segment(b.p, b.q, a.p))	s.insert(TPoint<long double>(a.p));
	if(on_segment(b.p, b.q, a.q))	s.insert(TPoint<long double>(a.q));
	return s;
}

template <typename T>
inline bool does_inter(const TSegment<T> &a, const TSegment<T> &b) {
	auto split = [](T l1, T r1, T l2, T r2) {
		if(r1 < l1)	swap(l1, r1);
		if(r2 < l2)	swap(l2, r2);
		return TPoint<T>::less(r1, l2) || TPoint<T>::less(r2, l1);
	};
	if(!split(a.p.x, a.q.x, b.p.x, b.q.x) && !split(a.p.y, a.q.y, b.p.y, b.q.y) &&
		sgn(det(a.p, a.q, b.p)) * sgn(det(a.p, a.q, b.q)) <= 0 &&
		sgn(det(b.p, b.q, a.p)) * sgn(det(b.p, b.q, a.q)) <= 0) {
		return true;
	}
	return false;
}

template <typename T>
struct TLine {
	TPoint<T> o;
	TPoint<T> d;
	
	TLine(const TPoint<T> &p, const TPoint<T> &q) : o(p), d(q - p) { }
	TLine(const T &a, const T &b, const T &c) {
		//ax + by = c
	}
	
	friend bool inter(const TLine &a, const TLine &b, TPoint<long double> &res) {
		if(TPoint<T>::equal(a.d * b.d, 0))	return false;
		long double t = (long double) (b.d * a.o + b.o * b.d) / 
						(long double) (a.d * b.d);
		res = a.o + a.d * t;
		return true;
	}
};

}; // geo

using namespace geo;

typedef TPoint<long long> Point;
typedef TSegment<long long> Segment;
