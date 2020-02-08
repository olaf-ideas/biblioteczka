#include <bits/stdc++.h>
using namespace std;
//sprawdz limity: malo - wskazniki, duzo - tablica

struct Node{
    unordered_map<char,Node*> m;    //Node* m[ALF];
    int cnt = 0;
    bool end = false;
}root;

struct Trie{
    void add(string& s, int ix = 0, Node* node = &root){
        if(ix == (int)s.size()){
            node->cnt++, node->end = true;
            return;
        }
        if(!node->m.count(s[ix]))   node->m[s[ix]] = new Node;
        node->cnt++;
        add(s, ix+1, node->m[s[ix]]);
    }

    int cntpref(string& s, int ix = 0, Node* node = &root){  //ile napisow z prefixem s
        if(ix == (int)s.size()) return node->cnt;
        if(!node->m.count(s[ix]))   return 0;
        return cntpref(s, ix+1, node->m[s[ix]]);
    }

    bool check(string& s, int ix = 0, Node* node = &root){  //sprawdz czy istieje napis s
        if(ix == (int)s.size()) return node->end;
        if(!node->m.count(s[ix]))   return false;
        return check(s, ix+1, node->m[s[ix]]);
    }
};

Trie trie;
int n,q;

int main(){
    cin >> n >> q;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        trie.add(s);
    }
    while(q--){
        string s;
        cin >> s;
        cout << trie.cntpref(s) << " " << trie.check(s) << "\n";   
    }
}