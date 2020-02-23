#include <bits/stdc++.h>
using namespace std;

struct Node{
    map<char,Node*> son;
    int cnt = 0;
    bool end = false;
}root;

struct Trie{
    void add(string& s, int pos = 0, Node* node = &root){
        node->cnt++;
        if(pos == (int)s.size()){
            node->end = true;          
            return;
        }
        if(!node->son.count(s[pos]))    node->son[s[pos]] = new Node;
        add(s, pos+1, node->son[s[pos]]);
    }

    bool check(string& s, int pos = 0, Node* node = &root){
        if(pos == (int)s.size())    return node->end;
        if(!node->son.count(s[pos]))    return false;
        return check(s, pos+1, node->son[s[pos]]);
    }

    int cnt_pref(string& s, int pos = 0, Node* node = &root){
        if(pos == (int)s.size())    return node->cnt;
        if(!node->son.count(s[pos]))    return 0;
        return cnt_pref(s, pos+1, node->son[s[pos]]);
    }

    void maxi(string& s, Node* node = &root){
        if(!node->son.size())   return;
        s += (*node->son.rbegin()).first;
        maxi(s, (*node->son.rbegin()).second);
    }

    void mini(string& s, Node* node = &root){
        if(!node->son.size())   return;
        s += (*node->son.begin()).first;
        mini(s, (*node->son.begin()).second);
    }
};

Trie trie;
int q;

int main(){
    cin >> q;
    while(q--){
        int type;
        string s;
        cin >> type >> s;
        if(type == 0)   trie.add(s);
        if(type == 1)   cout << trie.check(s) << "\n";
        if(type == 2)   cout << trie.cnt_pref(s) << "\n";
        if(type == 3)   s.clear(), trie.maxi(s), cout << s << "\n";
        if(type == 4)   s.clear(), trie.mini(s), cout << s << "\n";
    }
}