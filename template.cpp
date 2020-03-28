#ifndef PRAYFORSOLVE
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

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define st first
#define nd second
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)x.size()

using namespace std;
using namespace __gnu_pbds;

template <class key_type,class map_type=null_type> 
using hyper_set = tree<key_type,map_type,less<key_type>,rb_tree_tag,tree_order_statistics_node_update>;
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

const int MOD7 = 1000000007, MOD9 = 1000000009;
const ll INF = (1LL<<60LL);

/*------------------------------ CODE ---------------------------------*/

void solve(){
    
}

int main(){
    boost
    // int t;cin>>t;while(t--)solve();
    solve();
    cerr << "Execution time: " << (double)clock()/CLOCKS_PER_SEC << "\n";
}   