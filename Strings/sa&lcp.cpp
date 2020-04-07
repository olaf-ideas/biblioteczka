vector<int> suffix_array(string& s){
  int k = 0;
  vector<int> labels;
  for(int i = 0; i < (int)s.size(); i++)  labels.push_back(int(s[i]-'a'));
  while(1 << k < (int)s.size()){
    vector<pair<pair<int,int>,int>> tmp;
    for(int i = 0; i < (int)s.size(); i++)
      tmp.push_back(make_pair(make_pair(labels[i], i+(1<<k) < (int)s.size() ? labels[i + (1<<k)] : 1<<30), i));
    sort(tmp.begin(), tmp.end());
    for(int i = 0, l = 0; i < (int)tmp.size(); i++){
      if(i > 0 && tmp[i].first != tmp[i-1].first)
        l++;
      labels[tmp[i].second] = l;
    }
    k++;
  }
  vector<int> sa;
  sa.resie(s.size());
  for(int i = 0; i < (int)labels.size(); i++)
    sa[labels[i]] = i;
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