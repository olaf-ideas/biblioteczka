#include <bits/stdc++.h>
using namespace std;

struct node{
    int key, rank, size = 1;
    node *l = 0, *r = 0;
    node(int _key):key(_key),rank(rand()){}
};

int size(node* u){return u?u->size:0;}
void upd(node* u){u->size = 1+size(u->l)+size(u->r);}

node* merge(node* l, node* r){
    if(!l)  return r;
    if(!r)  return l;
    if(l->rank > r->rank){
        l->r = merge(l->r, r);
        upd(l);
        return l;
    }
    r->l = merge(l, r->l);
    upd(r);
    return r;
}

pair<node*, node*> split(node* p, int x){
    if(!p)  return {0,0};
    if(size(p->l) + 1 <= x){
        pair<node*, node*> q = split(p->r, x-size(p->l)-1);
        p->r = q.first;
        upd(p);
        return {p,q.second};
    }
    pair<node*, node*> q = split(p->l, x);
    p->l = q.second;
    upd(p);
    return {q.first, p};
}

node* root = 0;
void insert(int x){
    pair<node*, node*> q = split(root, x);
    node* t = new node(x);
    root = merge(q.first, merge(t, q.second));
}

int main(){

}