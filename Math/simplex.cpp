// 2h myslone, 2h pisane. Dziala
#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using matrix = vector<vector<ld>>;

const ld INF = 1000000000000000000;

ostream & operator << (ostream & o, const matrix & v) {
  for(int i = 0; i < (int)v.size()-1; i++) {
    for(int j = 0; j < (int)v[i].size(); j++) o << v[i][j] << ' ';
    o << '\n';
  }
  for(int i = 0; i < (int)v.back().size(); i++) o << v.back()[i] << ' ';
  return o;
}

template <class c>
ostream & operator << (ostream & o, const vector<c> & v) {
  for(int i = 0; i < (int)v.size(); i++)  cout << v[i] << ' ';
  return o;
}

struct Simplex {
  matrix A;
  int n, m, shift;
  vector<ld> b, c;
  vector<int> N;
  vector<int> B;
  ld v;
  Simplex(matrix & _A, vector<ld> & _b, vector<ld> & _c) : n(int(_c.size())), m(int(_A.size())), v(0) {
    // to do: initialize for more complex input
    shift = max(n, m);
    N.resize(n);
    B.resize(m);
    A.resize(2 * shift, vector<ld>(2 * shift));
    c.resize(2 * shift);
    b.resize(2 * shift);
    for(int i = 0; i < m; i++)
      for(int j = 0; j < n; j++)
        A[i+shift][j] = _A[i][j];
    
    for(int i = 0; i < n; i++)  N[i] = i;
    for(int i = 0; i < m; i++)  B[i] = shift + i;

    for(int i = 0; i < m; i++)  b[i+shift] = _b[i];  

    for(int i = 0; i < n; i++)  c[i] = _c[i];
  }

  vector<ld> operator () () {  // simplex
    while(1) {
      int e = -1;
      for(int i = 0; i < n; i++) {
        if(c[N[i]] > 0) {
          e = i;
          break;
        }
      }
      if(e == -1) break;

      vector<ld> d(m+shift, INF);
      int l = 0;  
      for(int i = 0; i < m; i++) {
        if(A[B[i]][N[e]] > 0) d[B[i]] = b[B[i]] / A[B[i]][N[e]];
        else                  d[B[i]] = INF;
        if(d[B[l]] > d[B[i]]) l = i;
      }

      if(d[B[l]] == INF)  cerr << "Unbounded\n", assert(false);
      else                pivot(e, l);
    }
    vector<bool> basic(2 * shift);
    for(int i = 0; i < m; i++)  basic[B[i]] = true;

    vector<ld> x(n);
    for(int i = 0; i < n; i++)
      if(basic[i])  x[i] = b[i];
      else          x[i] = 0;
    return x;
  }

  void pivot(int e, int l) {
    vector<ld> _b(b.size(), 0), _c(c.size(), 0);
    matrix _A(2 * shift, vector<ld>(2 * shift));
    ld _v = 0;
    _b[N[e]] = b[B[l]] / A[B[l]][N[e]];
    for(int i = 0; i < n; i++) {
      if(i == e)  continue;
      _A[N[e]][N[i]] = A[B[l]][N[i]] / A[B[l]][N[e]]; 
    }
    _A[N[e]][B[l]] = 1. / A[B[l]][N[e]];

    for(int i = 0; i < m; i++) {
      if(i == l)  continue;
      _b[B[i]] = b[B[i]] - A[B[i]][N[e]] * _b[N[e]];
      for(int j = 0; j < n; j++) {
        if(j == e)  continue;
        _A[B[i]][N[j]] = A[B[i]][N[j]] - A[B[i]][N[e]] * _A[N[e]][N[j]];
      }
      _A[B[i]][B[l]] = -A[B[i]][N[e]] * _A[N[e]][B[l]];
    }
    _v = v + c[N[e]] * _b[N[e]];
    for(int i = 0; i < n; i++) {
      if(i == e)  continue;
      _c[N[i]] = c[N[i]] - c[N[e]] * _A[N[e]][N[i]];
    }
    _c[B[l]] = -c[N[e]] * _A[N[e]][B[l]];

    A = _A;
    b = _b;
    c = _c;
    v = _v;

    swap(N[e], B[l]);
  }
};

/*
1) to do
  max c1 * x1 + ... + cn * xn

  a11 * x1 + a12 * x2 + ... + a1m * xm <= b1 
  a21 * x1 + a22 * x2 + ... + a2m * xm <= b2
                      .
                      .
                      .
  an1 * x1 + an1 * x2 + ... + anm * xm <= bm

2)  
  c1 c2 ...        cn

  a11 a12 a13 ... a1n  b1
  a21 a22              .
  a31     .            .
  .         .          .
  .           .
  .              
  am1             amn  bm
*/

int main(){
  int n, m;
  cin >> n >> m;
  vector<vector<ld>> a(m, vector<ld>(n));
  vector<ld> c(n), b(m);

  for(int i = 0; i < n; i++)  cin >> c[i];
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++)
      cin >> a[i][j];
    cin >> b[i];
  }

  Simplex s(a, b, c);

  cout << s() << '\n';
}

/*
 2 1
 1 1
 1 1 3
> 3 0

 3 5
 3  1  2
 1  1  3  30
 2  2  5  24
 4  1  2  36
 1  1  1  12
-1 -1 -1  12
> 8 4 0
*/
