vector<int> kmp(const string& s){
  vector<int> p(1);
  for(int i = 1, d = 0; i < (int)s.size(); i++){
    while(d > 0 && s[i] != s[d])  d = p[d-1];
    if(s[i] == s[d])  d++;
    p.push_back(d);
  }
  return p;
}