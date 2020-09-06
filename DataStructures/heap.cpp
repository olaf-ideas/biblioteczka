#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Heap {
  vector<T> h;
  Heap(const vector<T> a) : h(a){
    h.insert(h.begin(), 0);
    for(int i = (int)h.size() - 1; i > 1; i--)
      if(f(i, i >> 1))  swap(h[i], h[i >> 1]);
  }
  Heap() : h(1) {}

  bool f(int u, int p){return h[u] < h[p];}

  void _down(int u){
    int v = u, l = u << 1, r = u << 1 | 1;
    if(l < (int)h.size() && f(l, v)) v = l;
    if(r < (int)h.size() && f(r, v)) v = r;
    if(v != u)  swap(h[u], h[v]), _down(v);
  }

  void _up(int u){
    if(u == 1)  return;
    if(f(u, u >> 1))  swap(h[u], h[u >> 1]), _up(u >> 1);
  }

  void _print(){
    for(int i = 1; i < (int)h.size(); i++)
      cout << h[i] << ' ';
    cout << '\n';
  }

  void push(T &x){
    h.push_back(x);
    _up((int)h.size() - 1);
  }

  T pop(){
    assert(h.size() > 1);
    T r = h[1];
    swap(h[1], h.back()); h.pop_back();
    _down(1);
    return r;
  }

  T get(){assert(h.size()>1);return h[1];}
};
