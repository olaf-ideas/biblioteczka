#include <bits/stdc++.h>
using namespace std;

const int N = 5005;

int dp[N][N];
string a, b;

int lcs(){
  for(int i = 1; i <= (int)a.size(); i++)
    for(int j = 1; j <= (int)b.size(); j++)
      if(a[i-1] == b[j-1])  dp[i][j] = dp[i-1][j-1]+1;
      else                  dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
  return dp[a.size()][b.size()];
}

int lcs_count(int MOD){ // to do !
    
}

string lcs_string(){
  string r;
  int i = (int)a.size(), j = (int)b.size();
  while(i > 0 && j > 0)
    if(a[i-1] == b[j-1])              r += a[i-1], i--, j--;
    else if(dp[i-1][j] > dp[i][j-1])  i--;
    else                              j--;

  reverse(r.begin(), r.end());
  return r;
}

string lcs_lexicographic(){ //to do !

}

vector<string> lcs_gen(int x, int y){
  if(x == 0 || y == 0)    return vector<string>(1);

  if(a[x-1] == b[y-1]){
    vector<string> res = lcs_gen(x-1, y-1);
    for(string& s : res)    s += a[x-1];
    return res;
  }
  if(dp[x-1][y] > dp[x][y-1]) return lcs_gen(x-1, y);
  if(dp[x][y-1] > dp[x-1][y]) return lcs_gen(x, y-1);

  vector<string> t = lcs_gen(x-1, y), l = lcs_gen(x, y-1);
  t.insert(t.end(), l.begin(), l.end());
  return t;
}

int main(){
    cin >> a >> b;
    cout << "lcs lenght: " << lcs() << "\n";
    cout << "1 lcs: " << lcs_string() << "\n";
    cout << "all lcses:\n";

    vector<string> l = lcs_gen((int)a.size(), (int)b.size());
    sort(l.begin(), l.end());
    l.erase(unique(l.begin(), l.end()), l.end());
    
    for(string& s : l)
      cout << s << "\n"; 
}