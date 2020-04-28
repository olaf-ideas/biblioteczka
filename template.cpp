/*
#ifndef LOCAL
  #pragma GCC target("avx")
  #pragma GCC optimize("Ofast")
  #pragma GCC optimize("unroll-loops")
  #pragma comment(linker, "/stack:200000000")
  #pragma GCC target("sse,sse2,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
  #define boost ios_base::sync_with_stdio(0), cout.tie(0), cin.tie(0);
  #define db(x) x
#else
  #define boost ios_base::sync_with_stdio(0);
  #define db(x)   cerr << (#x) << ": " << x << "\n"
#endif
*/
#include <bits/stdc++.h>
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define st first
#define nd second
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)x.size()
*/
using namespace std;
/*
using namespace __gnu_pbds;

template <class key_type,class map_type=null_type> 
using hyper = tree<key_type,map_type,less<key_type>,rb_tree_tag,tree_order_statistics_node_update>;
using ll = long long;
using ld = long double;
using pi = pair<int,int>;
using pl = pair<ll,ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;
using upl = vector<pl>;
using si = set<int>;
using sl = set<ll>;
using spi = set<pi>;
using spl = set<pl>;
using mi = map<int,int>;
using ml = map<ll,ll>;
using mx = vector<vl>;

const double PI = 3.14159265359;
const double E = 2.71828182846;

double radian(double x){return x*PI/180;}
double degree(double x){return x*180/PI;}

template<class T,class U>T pot(T a, U b){T r=1;for(;b;a*=a,b>>=1)if(b&1)r*=a;return r;}
template<class T,class U,class M>T pot(T a, U b, M m){T r=1;for(a%=m;b;a=(a*a)%m,b>>=1)if(b&1)r=(r*a)%m;return r;}
template<class T,class M>T inv(T a, M m){return pot(a,m-2);}

const int MOD7 = 1000000007, MOD9 = 1000000009, INF = (1<<30);
const ll INFll = (1LL<<60LL);

struct Point{
  int x, y;
  friend ostream&operator << (ostream&o, const Point&p){o<<p.x<<' '<<p.y;return o;}
  friend istream&operator >> (istream&i, Point&p){i>>p.x>>p.y;return i;}
  // TO DO more functions
};
bool is_left(const Point& a,const Point& b,const Point& c){return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x)<0;}
*/

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

string sub(string a, string b){ // a >= b
  reverse(a.begin(), a.end()), reverse(b.begin(), b.end());
  assert(a.size() >= b.size() && (a.size() > b.size() || a >= b));
  string r;int f=0;
  for(int i=0;i<(int)b.size();i++){
    int s=a[i]-b[i]-f;f=0;if(s<0)s+=10,f=1;r+=char(s+48);
  }
  for(int i=(int)b.size();i<(int)a.size();i++){
    int s=a[i]-48-f;f=0;if(s<0)s+=10,f=1;r+=char(s+48);
  }
  while((int)r.size()>1&&r.back()=='0')r.pop_back();
  reverse(r.begin(), r.end());
  return r;
}


/*------------------------------ CODE ---------------------------------*/

void solve(){
  string a, b;
  cin >> a >> b;
  cout << add(a,b) << "\n";
  cout << sub(a,b) << "\n";
}

int main(){
  ios::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);
  // boost
  // int t;cin>>t;while(t--)solve();
  solve();
  cerr << "Execution time: " << (double)clock()/CLOCKS_PER_SEC << "\n";
}   
