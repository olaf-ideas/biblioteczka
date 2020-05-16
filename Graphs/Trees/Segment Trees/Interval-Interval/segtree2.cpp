#include <bits/stdc++.h>
using namespace std;

const int N = (1<<20);

int t[N * 2];

void upd(int l, int r, int v, int x=0, int y=N-1, int u=1){
	if(l > y || r < x)	return;
	if(l <= x && y <= r){
		t[u] += v;
		return;
	}
	int m = (x + y) >> 1;
	upd(l, r, v, x, m, u << 1);
	upd(l, r, v, m + 1, y, u << 1 | 1);
}

int ask(int p){
	int res = 0;
	for(p += N; p; p >>= 1)
		res += t[p];
	return res;
}

int main(){
	
}
