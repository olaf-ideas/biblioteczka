#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

typedef long long int ll;

string add(string a, string b){
  if(a.size() < b.size()) swap(a,b);
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  string r;
  int buf = 0;
  for(int i = 0; i < (int)b.size(); i++){
    int sum = a[i] + b[i] - 156 + buf;
    buf = 0;
    if(sum > 9) sum -= 10, buf = 1;
    r += sum + 48;
  }
  for(int i = (int)b.size(); i < (int)a.size(); i++){
    int sum = a[i] - 48 + buf;
    buf = 0;
    if(sum > 9) sum -= 10, buf = 1;
    r += sum + 48;
  }
  if(buf) r += buf + 48;
  reverse(r.begin(), r.end());

  return r;
}

string sub(string a, string b){ // a - b = r, r >= 0
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  string r;
  int buf = 0;
  for(int i = 0; i < (int)min(a.size(), b.size()); i++){
    int sum = a[i] - b[i] - buf;
    buf = 0;
    if(sum < 0) sum += 10, buf = 1;
    r += sum + 48;
  }
  for(int i = (int)b.size(); i < (int)a.size(); i++){
    int sum = a[i] - 48 - buf;
    buf = 0;
    if(sum < 0) sum += 10, buf = 1;
    r += sum + 48;
  }
  while((int)r.size() > 1 && r.back() == '0')  r.pop_back();
  reverse(r.begin(), r.end());

  return r;
}

int main(){
  string a, b;
  cin >> a >> b;
  cout << add(a,b) << '\n';
  cout << sub(a,b) << '\n';
}

const int B = 10000, D = 4;
struct BigInt{
  int l;
  vector<int> b;
  BigInt(int n){
    b.push_back(0);
    if(n == 0)  l = 1, b.push_back(0);
    else{
      l = 0;
      for(int i = 1; n; i++, n /= B)  
        l++, b.push_back(n%B);
    }
  }
  BigInt(){*this=BigInt(0);}
  BigInt(string&s){
    l = 0, b.push_back(0);
    for(int i = (int)s.size()-1; i >= 0; i -= D){
      int v = 0;
      for(int j = 0, p10 = 1; j < D && i-j >= 0; j++, p10*=10)
          v += (s[i-j]-'0')*p10;
      l++, b.push_back(v);
    }
  }
  friend ostream&operator<<(ostream&o,const BigInt&r){
    o << r.b[r.l];
    for(int i = r.l-1; i >= 1; i--) o << setfill('0') << setw(D) << r.b[i];
    return o;
  }
  friend istream&operator>>(istream&o,BigInt&r){
    string s;
    cin >> s;
    r = BigInt(s);
  } 
  BigInt operator+(const BigInt&r){
    BigInt f(*this);
    f.l = max(l, r.l);
    f.b.resize(f.l+5);
    for(int i = 1; i <= min(f.l, r.l); i++){
      f.b[i] += r.b[i];
      if(f.b[i] >= B)  f.b[i+1] += f.b[i] / B, f.b[i] %= B;
    }
    while(f.b[f.l+1])   f.l += 1;
    f.b.resize(f.l+1);
    return f;
  }

  BigInt operator-(const BigInt&r){
    BigInt f(*this);
    f.l = max(l, r.l);
    f.b.resize(f.l+5);
    for(int i = 1; i <= min(f.l, r.l); i++){
      f.b[i] -= r.b[i];
      while(f.b[i] < 0)   f.b[i] += B, f.b[i+1]--;
    }
    while(f.b[f.l] == 0)    f.l -= 1;
    f.b.resize(f.l+1);
    return f;
  }
  
  BigInt operator*(const BigInt&r){
    BigInt f = 0;
    f.l = l + r.l - 1;
    f.b.resize(f.l+5);
    for(int i = 1; i <= l; i++){
      for(int j = 1; j <= r.l; j++){
        f.b[i+j-1] += b[i] * r.b[j];
        if(f.b[i+j-1] / B)  f.b[i+j] += f.b[i+j-1] / B, f.b[i+j-1] %= B;
      }
    }
    while(f.b[f.l+1])   f.l += 1;
    f.b.resize(f.l+1);
    return f;
  }
  BigInt operator*(int r){
    return (*this) * BigInt(r);
  }
  BigInt operator/(int r){    //a > b
    BigInt f(*this);
    for(int i = f.l; i >= 1; i--)   f.b[i-1] += (f.b[i]%r) * B, f.b[i] /= r;
    while(f.b[f.l] == 0)    f.l -= 1;
    f.b.resize(f.l+1);
    return f;
  }
};