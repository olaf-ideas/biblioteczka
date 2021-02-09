#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define st first
#define nd second

using namespace std;

constexpr int T = 1e6;

int pr[T]; // priority
int ll[T]; // left child
int rr[T]; // right child
int ff[T]; // parent node (not used anywhere, but helpfull in some situations)
int sz[T]; // subtree size

int id[T];
bool rev[T];

int treap(int i) {
	static int _ = 1;
	sz[_] = 1;
	pr[_] = rand();
	
	id[_] = i;
	rev[_] = false;
	return _++;
}

void pull(int t) {
	if(!t)	return;
	sz[t] = sz[ll[t]] + 1 + sz[rr[t]];
	
	if(ff[t] && ll[ff[t]] != t && rr[ff[t]] != t)	ff[t] = 0;
	
	if(ll[t])	ff[ll[t]] = t;
	if(rr[t])	ff[rr[t]] = t;
} 

void push(int t) {
	if(!t)	return;
	
	if(rev[t]) {
		swap(ll[t], rr[t]);
		if(ll[t])	rev[ll[t]] ^= true;
		if(rr[t])	rev[rr[t]] ^= true;
		rev[t] = false;
	}
}

int merge(int l, int r) {
	if(!l || !r)	return l ? l : r;
	push(l), push(r);
	if(pr[l] < pr[r])	return rr[l] = merge(rr[l], r), pull(l), l;
	else				return ll[r] = merge(l, ll[r]), pull(r), r;
}

void split(int t, int cnt, int &l, int &r) {
	if(!t)	return void(l = r = 0);
	push(t);
	if(sz[ll[t]] >= cnt)	split(ll[t], cnt, l, ll[t]), r = t;
	else					split(rr[t], cnt - sz[ll[t]] - 1, rr[t], r), l = t;
	pull(t);
}

void reverse(int t, int l, int r) {
	assert(l <= r);
	int t1, t2, t3;
	split(t, l, t1, t2);
	split(t2, r - l + 1, t2, t3);
	rev[t2] ^= true;
	push(t2);
	t = merge(t1, merge(t2, t3));
}

void print(int t) {
	if(!t)	return;
	push(t);
	print(ll[t]);
	cout << id[t] << ' ';
	print(rr[t]);
}

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);
	
	int root = 0;
	
	int n; cin >> n;
	for(int i = 0; i < n; i++) {
		root = merge(root, treap(i));
	}
	
	int l, r; cin >> l >> r;
	reverse(root, l, r);
	
	print(root);
	cout << '\n';
}
