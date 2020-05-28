vector<int> suffixArray(const string &s){
  const int n = s.size();
  vector<int> sa(n), eqv(n), nexteqv(n);
  for(int i = 0; i < n; i++)  eqv[sa[i] = i] = s[i];
  int chunk = 1;
  auto cmp = [&chunk, n, &s, &eqv](int x, int y){
    if(eqv[x] != eqv[y]) return eqv[x] < eqv[y];
    if(x + chunk >= n || y + chunk >= n) return x > y;
    return eqv[x + chunk] < eqv[y + chunk];
  };
  do{
    sort(sa.begin(), sa.end(), cmp);
    nexteqv[sa[0]] = 0;
    for(int i = 1; i < n; i++)
      nexteqv[sa[i]] = nexteqv[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
    eqv.swap(nexteqv);
    chunk <<= 1;
  }while(eqv[sa[n - 1]] < n - 1);
  return sa;
}

vector<int> lcp(string& s, vector<int>& sa){
  vector<int> lcp, rank;
  rank.resize(sa.size());
  lcp.resize(sa.size());
  for(int i = 0; i < (int)sa.size(); i++)
    rank[sa[i]] = i;
  int l = 0;
  for(int i = 0; i < (int)sa.size(); i++){
    if(rank[i] == (int)sa.size()-1) lcp[rank[i]] = 0;
    else{
      while(i+l < (int)s.size() && 
            sa[rank[i]+1]+l < (int)s.size() && 
            s[i+l] == s[sa[rank[i]+1]+l])
        l++;
      lcp[rank[i]] = l;
    }
    l = max(0, l-1);
  }
  return lcp;
}
