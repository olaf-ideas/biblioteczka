template<int N>
struct UF{
  vector<int> uf;
  UF() : uf(N) {iota(uf.begin(), uf.end(), 0);}
  int Find(int u){return uf[u] == u ? u : uf[u] = Find(uf[u]);}
  bool Union(int u, int v){
    u = Find(u), v = Find(v);
    return u != v ? false : (uf[u] = v, true);
  }
}; // Usage: UF<100> uf;
