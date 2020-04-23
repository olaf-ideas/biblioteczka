#include <bits/stdc++.h>
using namespace std;

struct Node{
    map<char,Node*> s;
    int c = 0, e = 0;
}root;

struct Trie{
  void add(string& s, int i = 0, Node* n = &root){
    n->c++;
    if(i == (int)s.size()){
        n->e++;
        return;
    }
    if(!n->s.count(s[i]))    n->s[s[i]] = new Node;
    add(s,i+1,n->s[s[i]]);
  }

  bool check(string& s, int i = 0, Node* n = &root){
    if(i == (int)s.size())    return n->e;
    if(!n->s.count(s[i]))   return false;
    return check(s,i+1,n->s[s[i]]);
  }

  void mini(string& r, Node* n = &root){
    if(n->s.empty())    return;
    r += n->s.begin()->first;
    maxi(r,n->s.begin()->second);
  }

  void maxi(string& r, Node* n = &root){
    if(n->s.empty())    return;
    r += n->s.rbegin()->first;
    maxi(r,n->s.rbegin()->second);
  }

  int cnt_pref(string& s, int i = 0, Node* n = &root){
    if(i == (int)s.size())  return n->c;
    if(!n->s.count(s[i]))   return 0;
    return cnt_pref(s,i+1,n->s[s[i]]);
  }
};

Trie t;
int q;

int main(){
  cin >> q;
  while(q--){
    int type;
    string s;
    cin >> type >> s;
    if(type == 0)   t.add(s);
    if(type == 1)   cout << t.check(s) << "\n";
    if(type == 2)   cout << t.cnt_pref(s) << "\n";
    if(type == 3)   s.clear(), t.maxi(s), cout << s << "\n";
    if(type == 4)   s.clear(), t.mini(s), cout << s << "\n";
  }
}