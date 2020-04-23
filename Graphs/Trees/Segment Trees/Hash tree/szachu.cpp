#include<bits/stdc++.h>
using namespace std;

const int pot=(1<<17);
const int maxn=(int)1e5+10;
const int mod=(int)1e9+696969;
const int sp=31;
long long Lt[pot*2+10];//hasze od lewej
long long Rt[pot*2+10];//hasze od prawej
long long pott[pot+10];
int sajz[pot*2+10];
char s[maxn];
int n;

void prep()
{
	pott[0]=1;
	pott[1]=sp;
	for(int i=2;i<=pot;i++)
		pott[i]=(pott[i-1]*sp)%mod;
	for(int i=1;i<=n;i++)
	{
		Lt[i+pot]=(s[i]-'a'+1);
		Rt[i+pot]=(s[i]-'a'+1);
	}
	for(int i=pot;i<(pot<<1);i++)
		sajz[i]=1;
	for(int i=(pot-1);i>=1;i--)
	{
		sajz[i]=(sajz[i<<1]<<1);
		Lt[i]=(Lt[i<<1]+Lt[i<<1^1]*pott[sajz[i<<1]])%mod;
		Rt[i]=(Rt[i<<1]*pott[sajz[i<<1]]+Rt[i<<1^1])%mod;
	}
}

void updt(int a, int war)
{
	Lt[a+=pot]=war;
	Rt[a]=war;
	for(int b=a>>1; b; b>>=1)
		Rt[b]=(Rt[b<<1]*pott[sajz[b<<1]]+Rt[b<<1^1])%mod;
	for(int b=a>>1; b; b>>=1)
		Lt[b]=(Lt[b<<1]+Lt[b<<1^1]*pott[sajz[b<<1]])%mod;
}

int query(int a, int b, int kind)
{
	int aa=a,bb=b;
	pair<long long,int> retL=make_pair(0,0);
	pair<long long,int> retR=make_pair(0,0);
	for(a+=pot-1,b+=pot+1; a/2!=b/2; a>>=1,b>>=1)
	{
		if(!(a&1))
		{
			retL.second+=(sajz[a+1]);
			if(kind=='R')
				retL.first=(retL.first+pott[(bb-aa+1)-retL.second]*Rt[a+1])%mod;
			if(kind=='L')
				retL.first=((retL.first)+pott[retL.second-sajz[a+1]]*Lt[a+1])%mod;
		}
		if(b&1)
		{
			retR.second+=(sajz[b-1]);
			if(kind=='R')
				retR.first=((retR.first)+pott[retR.second-sajz[b-1]]*Rt[b-1])%mod;
			if(kind=='L')
				retR.first=(retR.first+pott[(bb-aa+1)-retR.second]*Lt[b-1])%mod;
		}
	}
	if(kind=='R')
		return (retR.first+retL.first)%mod;
	if(kind=='L')
		return (retL.first+retR.first)%mod;
}


int check(int start, int kind)
{
	if(kind==2)//nieparzysty
	{
		int l=1,r=min(start-1,n-start);
		while(r-l>1)
		{
			int mid=l+(r-l)/2;
			if(query(start-mid,start-1,'L')==query(start+1,start+mid,'R'))
				l=mid;
			else
				r=mid;
		}
		if(query(start-r,start-1,'L')==query(start+1,start+r,'R'))
			return r*2+1;
		if(l==1 && s[start-1]!=s[start+1])
			return 1;
		return l*2+1;
	}
	else
	{
		int l=1,r=min(start,n-start);
		while(r-l>1)
		{
			int mid=l+(r-l)/2;
			if(query(start-mid+1,start,'L')==query(start+1,start+mid,'R'))
				l=mid;
			else
				r=mid;
		}
		if(query(start-r+1,start,'L')==query(start+1,start+r,'R'))
			return r*2;
		if(l==1 && s[start]!=s[start+1])
			return -1;
		return l*2;
	}
}

int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
  prep();
	for(int i = 1; i <= n; i++){
    string a;
    for(int j = i; j <= n; j++){
      a += s[j];
      for(int k = 1; k <= n; k++){
        string b;
        for(int l = k; l <= n; l++){
          b += s[l];
          bool x = (query(i, j, 'L') == query(k, l, 'L'));
          bool y = (a == b);
          if(x != y)  cout << a << " " << b << "\n";
        }
      }
    }
  }
}


const int N = (1<<17), MOD = 1000696969, ALF = 31;
ll h[N*2+10];
ll p[N+10];
int s[N*2+10];
char t[N+10];

void prep(int n){
  p[0] = 1;
  for(int i = 1; i <= N; i++) p[i] = (p[i-1]*ALF) % MOD;
  for(int i = 1; i <= n; i++)
    h[i+N] = t[i] - 'a' +1;
  for(int i = N; i < (N<<1); i++) s[i] = 1;
  for(int i = N-1; i >= 1; i--){
    s[i] = s[i<<1]<<1;
    h[i] = (h[i<<1] + h[i<<1|1] * p[s[i<<1]]) % MOD;
  }
}

void upd(int a, char ch){
  h[a += N] = ch - 'a' +1;
  for(;a>>=1;)
    h[a] = (h[a<<1] + h[a<<1|1] * p[s[a<<1]]) % MOD;
}

ll ask(int l, int r){
  int lll = l, rrr = r;
  pair<ll,int> rl = make_pair(0,0);
  pair<ll,int> rr = make_pair(0,0);
  for(l += N-1, r += N+1; l/2 != r/2; l >>= 1, r >>= 1){
    if(!(l&1)){
      rl.second += s[l+1];
      rl.first = (rl.first + h[l+1] * p[rl.second - s[l+1]]) % MOD;
    }
    if(r&1){
      rr.second += s[r-1];
      rr.first = (rr.first + h[r-1] * p[rrr-lll+1 - rr.second]) % MOD;
    }
  }
  return (rl.first + rr.first) % MOD;
}