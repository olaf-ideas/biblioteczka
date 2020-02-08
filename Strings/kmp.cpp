#include <bits/stdc++.h>
using namespace std;

vector<int> kmp(string &s){     //najdluzszy prefixo-sufix  abaab => ab
    vector<int> pi(s.size());
    for(int i = 1, d = 0; i < (int)s.size(); i++){
        while(d > 0 && s[i] != s[d])    d = pi[d-1];
        if(s[i] == s[d])    d++;
        pi[i] = d;
    }
    return pi;
}

int main(){
    
}