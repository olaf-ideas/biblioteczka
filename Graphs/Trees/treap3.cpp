#include <bits/stdc++.h>
using namespace std;

const int N = 300005;

struct Node{
  int key, rank, sons;
  Node *l, *r, *p;
  bool rev;
  bool rev_state;

  Node(int _key):key(_key),rank(rand()),sons(0),l(0),r(0),p(0),rev(0),rev_state(0){}
};

int size(Node *t){
  return t ? t->sons : 0;
}

void fix(Node *t){
  if(!t)  return;
  if(t->l)  t->l->p = t;
  if(t->r)  t->r->p = t;
  t->sons = (t->l ? t->l->sons + 1 : 0) + (t->r ? t->r->sons + 1 : 0);
}

void lazy(Node* it){
  if(it && it->rev){
    it->rev = 0;
    it->rev_state ^= 1;
    swap(it->l, it->r);
    if(it->l) it->l->rev ^= 1;
    if(it->r) it->r->rev ^= 1;
  }
}

void merge(Node* &t, Node* l, Node* r){
  lazy(l); lazy(r);

  if(!l || !r)
      t = l ? l : r;
  else if(l->rank > r->rank)
      merge(l->r, l->r, r), t = l;
  else
      merge(r->l, l, r->l), t = r;

  fix(t);
}

void split(Node* t, Node* &l, Node* &r, int pos, int add = 0){
  if(!t) l = r = NULL;
  else{
    lazy(t);
    int cur_pos = add + (t->l? 1 + t->l->sons : 0);

    if(pos <= cur_pos)
      split(t->l, l, t->l, pos, add), r = t;
    else
      split(t->r, t->r, r, pos, cur_pos + 1), l = t;

    fix(t);
  }
}

void insert(Node* &t, Node* &it, int pos, int add = 0) {
  if(!t)	t = it;
  else{
    lazy(t);
    int cur_pos = add + (t->l ? 1 + t->l->sons : 0);

    if(it->rank > t->rank){
      split(t, it->l, it->r, pos, add), t = it;
    }else{
      if(pos <= cur_pos) insert(t->l, it, pos, add);
      else insert(t->r, it, pos, cur_pos + 1);
    }
    fix(t);
  }
}

void reverse(Node* t, int l, int r){
  Node *t1,*t2,*t3;

  split(t, t1, t2, l);
  split(t2, t2, t3, r-l+1);

  t2->rev ^= 1;
  merge(t, t1, t2);
  merge(t, t, t3);
}

int index(Node* t, int key){
  if(!t)  return 0;
  lazy(t);
  if(t->key == key) return t->rev_state ? size(t->r) + 1 : size(t->l) + 1;
  if(t->rev_state){
    if(t->key < key)  return index(t->l, key) + size(t->r) + 1;
    return index(t->l, key);
  }
  if(t->key < key)  return index(t->r, key) + size(t->l) + 1;
  return index(t->r, key);
}

int index(Node* t){
  if(!t->p) return size(t->l) + 1;
  lazy(t->p);
  if(t->p->r == t)  return index(t->p) + size(t->l) + 1;
  return index(t->p) - size(t->r) - 1;
}

void lazy_up(Node* t){
  if(!t)  return;
  lazy_up(t->p);
  lazy(t);
  fix(t);
}

ostream& operator << (ostream& o, Node *t){
  if(!t)  return o;
  lazy(t);
  o << t->l;
  o << t->key << " ";
  o << t->r;
  return o;
}

int n, id[N];
vector<Node*> a;

int main(){
  srand(time(NULL));
  a.push_back(0);
  cin >> n;
  for(int i = 1; i <= n; i++){
    int x;
    cin >> x;
    id[x] = i;
    a.push_back(new Node(x));
    insert(a[0], a.back(), i);
  }

  cout << "normal: " << a[0] << "\n";
  // reverse(a[0], 0, n-1);
  cout << "reversed: " << a[0] << "\n";

  cout << "index: ";
  for(int i = 1; i < (int)a.size(); i++)  lazy_up(a[i]), cout << index(a[i]) << " ";
  cout << "\n";

}