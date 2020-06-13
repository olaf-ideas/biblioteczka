template <class T>
struct Fenwick {
  vector<T> s;
  Fenwick(int n) : s(n) {}
  void upd(int p, T v){
    for(; p < (int)s.size(); p |= p + 1)  s[p] += v;
  }
  T ask(int p){ // [0, p)
    T r = 0;
    for(; p; p &= p - 1)  r += s[p - 1];
    return r;
  }
  int lower_bound(T x){
    if(x <= 0)  return -1;
    int p = 0;
    for(int i = 1 << 25; i; i >>= 1)
      if(p + i <= (int)s.size() && s[p + i - 1] < x)
        p += i, x -= s[p - 1];
    return p;
  }
};
