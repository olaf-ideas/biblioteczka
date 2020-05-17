#include <vector>
using namespace std;

template<class T>
struct SegTree{
  T f(T&a, T&b){return max(a,b);}
  static constexpr T unit = INT_MIN;
  
  vector<T> t;int n;
  SegTree(int n = 0, T d = 0):t(2*n, d),n(n){}
  void upd(int p, T v){
    for(t[p+=n] = v; p >>= 1;)
      t[p] = f(t[p<<1],t[p<<1|1]);
  }
  T ask(int l, int r){    // query [l, r)
    T ra = unit, la = unit;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1){
      if(l&1) la = f(ra, t[l++]);
      if(r&1) ra = f(s[--r], ra);
    }
    return f(ra, rb);
  }
};