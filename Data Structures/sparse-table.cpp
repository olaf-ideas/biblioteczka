template <class T>
struct SparseTable {
  const vector<T> &x;
  vector<vector<int>> table;
  int argmin(int i, int j){return x[i] < x[j] ? i : j;}
  
  SparseTable(const vector<T> &_x) : x(_x) {
    int logn = sizeof(int) * __CHAR_BIT__ - 1 - __builtin_clz(x.size());
    table.assign(logn + 1, vector<int>(x.size()));
    iota(table[0].begin(), table[0].end(), 0);
    for(int h = 0; h < logn; h++)
      for(int i = 0; i + (1 << h) < (int)x.size(); i++)
        table[h + 1][i] = argmin(table[h][i], table[h][i + (1 << h)]);
  }
  T range_min(int i, int j){
    int h = sizeof(int) * __CHAR_BIT__ - 1 - __builtin_clz(j - i);
    return x[argmin(table[h][i], table[h][j - (1 << h)])];
  }
};
