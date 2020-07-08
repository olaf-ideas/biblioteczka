#include <bits/stdc++.h>
using namespace std;

// r[i] = promien najdluzszego palindromu parzystego o srodku w (i, i + 1)
vector<int> manacher_even(const string &s){
  string x("$"); x += s; x += '#';
  vector<int> r(1);
  for(int i = 1, j = 0; i < (int)x.size(); ){
    while(x[i - j] == x[i + j + 1]) j++;
    r.push_back(j);
    int k = 1;
    while(r[i - k] != r[i] - k && k <= j)
      r.push_back(min(r[i - k], r[i] - k)), k++;
    j = max(0, j - k), i += k;
  }
  r.erase(r.begin()), r.pop_back();
  return r;
}

// r[i] = promien najluzszego palindromu nieparzystego o srodku w i
vector<int> manacher_odd(const string &s){
  string x("$"); x += s, x += '#';
  vector<int> r(1);
  for(int i = 1, j = 0; i < (int)x.size(); ){
    while(x[i - j - 1] == x[i + j + 1]) j++;
    r.push_back(j);
    int k = 1;
    while(r[i - k] != r[i] - k && k <= j)
      r.push_back(min(r[i - k], r[i] - k)), k++;
    j = max(j - k, 0), i += k;    
  }
  r.erase(r.begin()), r.pop_back();
  return r;
}

int main(){
  string s;
  cin >> s;
  vector<int> even = manacher_even(s);
  vector<int> odd = manacher_odd(s);
  for(int i = 0; i < (int)even.size(); i++) cout << even[i] << ' ';
  cout << '\n';
  for(int i = 0; i < (int)odd.size(); i++)  cout << odd[i] << ' ';
  cout << '\n';  
}
