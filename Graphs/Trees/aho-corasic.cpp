// Aho Corasic algorithm  O(|s| + |t|)

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

const int S = 100005, ALF = 27;

int go[S][ALF], fail[S*ALF], cnt = 1;
vector<int> leaf[S*ALF];

void add_string(const string& s, int id){
  int u = 0;
  for(char ch : s){
    int c = ch - 'a';
    if(!go[u][c]) go[u][c] = cnt++;
    u = go[u][c];
  } 
  leaf[u].push_back(id);
}

void build(){
  queue<pair<int,int>> q;
  for(int i = 0; i < ALF; i++)
    if(go[0][i])  q.push({go[0][i], 0});
  while(!q.empty()){
    auto p = q.front(); q.pop();
    int u = p.first, f = p.second;
    fail[u] = f;
    for(int i = 0; i < ALF; i++){
      if(go[u][i])  q.push({go[u][i], go[f][i]});
      else          go[u][i] = go[f][i];
    }
  }
}

int next(int u, char ch){
  int c = ch-'a';
  if(go[u][c])  return go[u][c];
  if(u == 0)    return 0;
  return next(fail[u], ch);
}