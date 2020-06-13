struct Treap {
  Treap * left, right;
  int size;
};

int size(Treap * t){return t ? t->size : 0;}
