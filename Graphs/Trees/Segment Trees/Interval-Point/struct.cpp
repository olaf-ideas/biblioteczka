#include <bits/stdc++.h>
using namespace std;

struct Segtree{
	vector<int> t;
	int base;
	Segtree(int n, int d=0) : base(1 << (32 - __builtin_clz(n - 1))){
		t.resize(base << 1, d);
	}
	
	void upd(int l, int r, int v, int x=0, int y=-1, int u=1){
		if(y == -1)	y += base;
		if(r < x || y < l)	return;
		if(l <= x && y <= r){
			t[u] += v;
			return;
		}
		int m = (x + y) >> 1;
		upd(l, r, v, x, m, u << 1);
		upd(l, r, v, m + 1, y, u << 1 | 1);
	}

	int ask(int p){
		int r = 0;
		for(p += base; p; p >>= 1)
			r += t[p];
		return r;
	}
};

int main(){
	Segtree a(1000000);
	cout << "SIZE: " << a.t.size() << '\n';
	cout << "BASE: " << a.base << '\n';
	a.upd*	
}
