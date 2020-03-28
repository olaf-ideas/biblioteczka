#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005, ALF = 'z'-'a'+2, TRIE = MAXN*ALF;

int n, trie[TRIE][ALF], cnt[TRIE], nodes = 1, e[TRIE];

void add(string& s, int i = 0, int node = 1){
    cnt[node]++;
    if(i == (int)s.size()){
        e[node]++;
        return;
    }
    if(!trie[node][s[i]-'a'])   trie[node][s[i]-'a'] = ++nodes;
    add(s, i+1, trie[node][s[i]-'a']);
}

void remove(string& s, int i = 0, int node = 1){
    cnt[node]--;
    if(i == (int)s.size()){
        e[node]--;
        return;
    }
    remove(s, i+1, trie[node][s[i]-'a']);
    if(cnt[trie[node][s[i]-'a']])   trie[node][s[i]-'a'] = 0;
}

int main(){

}