#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void counting_sort(vector<ll> &x, ll p){
    vector<ll> cnt(10,0), ans(x.size());
    for(int i = 0; i < x.size(); i++)       cnt[(x[i]/p)%10]++;
    for(int i = 1; i < 10; i++)             cnt[i] += cnt[i-1];
    for(int i = x.size()-1; i >= 0; i--)    ans[--cnt[(x[i]/p)%10]] = x[i];
    x = ans;
}

void radix_sort(vector<ll> &x){
    for(ll p = 1, i = 1; i <= 18; p*=10, i++)  counting_sort(x,p);
}

int n;
vector<ll> x;

int main(){
    scanf("%d", &n);
    x.resize(n);
    for(int i = 0; i < n; i++)  scanf("%lld", &x[i]);

    radix_sort(x);
    
    for(int i = 0; i < n; i++)  printf("%lld ", x[i]);
    printf("\n");
}