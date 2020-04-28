#include <bits/stdc++.h>
using namespace std;

string add(string a, string b){
  if(a.size()<b.size())swap(a,b);
  reverse(a.begin(),a.end()),reverse(b.begin(),b.end());
  string r;int f=0;
  for(int i=0;i<(int)b.size();i++){
    int s=a[i]+b[i]-96+f;f=0;if(s>9)s-=10,f=1;r+=char(s+48);
  }
  for(int i=(int)b.size();i<(int)a.size();i++){
    int s=a[i]-48+f;f=0;if(s>9)s-=10,f=1;r+=char(s+48);
  }
  if(f)r+=char(f+48);
  reverse(r.begin(), r.end());
  return r;
}

int main(){
  string a, b;
  cin >> a >> b;
  cout << add(a,b) << "\n";
}
