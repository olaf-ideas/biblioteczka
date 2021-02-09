/*
 * Author: olaf-ideas
 * License: CC0
 * Description: Treap structure implementation with range reversal
 * Status: tested
 * Complexity: O(log n)
 * Link: 
 */

#include <iostream>
#include <cassert>
#include <random>

struct Treap {
	int size, prior;
	Treap *l, *r, *p;
	
	/* data */
	bool rev;
	int id;
	Treap(int _id) : size(1), prior(rand()), l(0), r(0), p(0) {
		rev = false;
		id = _id;
	}
};

int size(const Treap *t) { return t ? t->size : 0; }

void pull(Treap *t) {
	if(!t)	return;
	t->size = size(t->l) + 1 + size(t->r);
	if(t->p && t->p->l != t && t->p->r != t)
		t->p = 0;
	if(t->l)	t->l->p = t;
	if(t->r)	t->r->p = t;
}

void push(Treap *t) {
	if(!t)	return;
	if(t->rev) {
		std::swap(t->l, t->r);
		if(t->l)	t->l->rev ^= true;
		if(t->r)	t->r->rev ^= true;
		t->rev = false;
	}
}

Treap* merge(Treap *l, Treap *r) {
	if(!l || !r)	return l ? l : r;
	push(l), push(r);
	if(l->prior < r->prior)
		return l->r = merge(l->r, r), pull(l), l;
	else
		return r->l = merge(l, r->l), pull(r), r;
	assert(69 == 420);
}

void split(Treap *t, int cnt, Treap *&l, Treap *&r) {
	if(!t)	return void(l = r = 0);
	push(t);
	if(size(t->l) >= cnt)
		split(t->l, cnt, l, t->l), r = t;
	else
		split(t->r, cnt - size(t->l) - 1, t->r, r), l = t;
	pull(t);
}

void reverse(Treap *&t, int l, int r) {
	assert(l <= r);
	Treap *t1, *t2, *t3;
	split(t, l, t1, t2);
	split(t2, r - l + 1, t2, t3);
	assert(t2);
	t2->rev ^= true;
	push(t2);
	t = merge(t1, merge(t2, t3));
}

void update_path(Treap *t) {
	if(!t)	return;
	update_path(t->p);
	push(t);
}

int _get_index(Treap *t) {
	assert(t);
	push(t);
	if(!t->p)	return size(t->l);
	if(t->p->r == t)	return _get_index(t->p) + size(t->l) + 1;
	return _get_index(t->p) - size(t-> r) - 1;
}

int get_index(Treap *t) {
	update_path(t);
	return _get_index(t);
}

void print(Treap *t) {
	if(!t)	return;
	push(t);
	print(t->l);
	std::cout << t->id << ' ';
	print(t->r);
}

/* Usage
Treap *t[10000];

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);
	
	int n; cin >> n;
	for(int i = 0; i < n; i++) {
		t[0] = merge(t[0], new Treap(i));
	}
	
	int l, r; cin >> l >> r;
	reverse(t[0], l, r);
	print(t[0]);
	cout << '\n';
}
*/
