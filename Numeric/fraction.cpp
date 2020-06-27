template <class T>
struct Fraction {
  T l, m;
  Fraction(T _l, T _m){
    T g = __gcd(_l, _m);
    l = _l / g, m = _m / g;
  }
  Fraction() : l(1), m(1) {}
  Fraction operator + (const Fraction &other) const {return Fraction(l * other.m + other.l * m, m * other.m);}
  Fraction operator - (const Fraction &other) const {return Fraction(l * other.m - other.l * m, m * other.m);}
  Fraction operator * (const Fraction &other) const {return Fraction(l * other.l, m * other.m);}
  Fraction operator / (const Fraction &other) const {return Fraction(l * other.m, m * other.l);}
  friend ostream& operator << (ostream & o, const Fraction &f){return o << f.l << '/' << f.m;}
  friend istream& operator >> (istream & i, Fraction & f){return i >> f.l >> f.m;}

  template <class U>
  friend Fraction pot (const Fraction & f, U k){
    Fraction res(1, 1), a(f.l, f.m);
    if(k < 0) swap(a.l, a.m), k = -k;
    for(; k; k >>= 1, a = a * a)
      if(k & 1) res = res * a;
    return res;
  }
  
  template <class U>
  operator U() const {
    return U(l) / U(m);
  }
};
