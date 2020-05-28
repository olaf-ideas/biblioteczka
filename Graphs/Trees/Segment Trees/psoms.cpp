#include <bits/stdc++.h>
#define st first
#define nd second
#define ll long long
#define node pair<pair<ll,ll>,pair<ll,ll>>
using namespace std;

const int T = 1 << 20;

node t[T << 1];
int n, q;

node merge(const node & l, const node & r){
  return {{l.st.st + r.st.st, max({l.st.nd, r.st.nd, l.st.st + r.st.st, l.nd.nd + r.nd.st})},
          {max(l.nd.st,l.st.st + r.nd.st), max(r.nd.nd, r.st.st + l.nd.nd)}};
}

void upd(int x, int v){
  t[x += T] = {{v,max(0,v)},{max(0,v),max(0,v)}};
  while(x >>= 1)  t[x] = merge(t[x << 1], t[x << 1 | 1]);
}

ll ask(int l, int r){
  if(l == r)  return t[l += T].st.nd;
  node lt(t[l += T]), rt(t[r += T]);
  for(; l + 1 < r; l >>= 1, r >>= 1){
    if(!(l & 1))  lt = merge(lt, t[l + 1]);
    if(r & 1)     rt = merge(t[r - 1], rt);
  }
  return merge(lt, rt).st.nd;
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for(int i = 1; i <= n; i++){
    int a; cin >> a;
    upd(i, a);
  }  

  cin >> q;
  while(q--){
    char c;
    int a, b;
    cin >> c >> a >> b;
    if(c == 'Q')  cout << ask(a, b) << '\n';
    if(c == 'C')  upd(a, b);    
  }
}
