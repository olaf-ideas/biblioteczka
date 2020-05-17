// pryma sort trie, operacje: O(|s|)
#include <string>
using namespace std;

const int S = 100005, ALF = 26;

int t[S][ALF], c[S*ALF], cnt = 1, e[S*ALF];

void add(const string& s){
  int u = 0;
  for(int i = 0; i < (int)s.size(); i++){
    c[u]++;
    if(!t[u][s[i]-'a']) t[u][s[i]-'a'] = ++cnt;
    u = t[u][s[i]-'a'];
  }
  e[u]++;
}

void remove(const string& s){
  int u = 0;
  for(int i = 0; i < (int)s.size(); i++){
    c[u]--;
    u = t[u][s[i]-'a'];
  }
  e[u]--;
}