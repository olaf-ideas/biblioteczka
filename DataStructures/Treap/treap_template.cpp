// O(log n) * ~2.4
struct Treap {
    int size, prior;
    Treap *l, *r, *p;

    /* data */

    Treap() : size(1), prior(rand()), l(0), r(0), p(0) {
        
    }
};

int size(Treap *t) { return t ? t->size : 0; }

void pull(Treap *t) {
    if(!t)  return;
    t->size = size(t->l) + 1 + size(t->r);
    if(t->p && t->p->l != t && t->p->r != t)
        t->p = 0;
    if(t->l)    t->l->p = t;
    if(t->r)    t->r->p = t;
    
}

void push(Treap *t) {
    if(!t) return;
    
    pull(t);
}

Treap *merge(Treap *l, Treap *r) {
    if(!l || !r)    return l ? l : r;
    push(l), push(r);
    if(l->prior < r->prior)
        return l->r = merge(l->r, r), pull(l), l;
    else
        return r->l = merge(l, r->l), pull(r), r;
}

void split(Treap *t, int cnt, Treap *&l, Treap *&r) {
    if(!t)  return void(l = r = 0);
    push(t);
    if(size(t->l) >= cnt)
        split(t->l, cnt, l, t->l), r = t;
    else
        split(t->r, cnt - size(t->l) - 1, t->r, r), l = t;
    pull(t);
}
