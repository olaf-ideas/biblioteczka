#include <bits/stdc++.h>
using namespace std;

struct treap
{
  int v;
  int rank;
  int r;
  treap *lewe = 0;
  treap *prawe = 0;
  treap *rodzic = 0;
  bool odwroc = false;
  
  treap(int _v): v(_v)
  {
    r = 1;
    rank = rand();
  }
  
  void propaguj()
  {
    if (odwroc)
    {
      odwroc = false;
      swap(lewe, prawe);
      if (lewe) lewe->odwroc ^= 1;
      if (prawe) prawe->odwroc ^= 1;
    }
  }
};

int rozmiar(treap *a)
{
  return a ? a->r : 0;
}

void policz_rozmiar(treap *a)
{
  a->r = 1 + rozmiar(a->lewe) + rozmiar(a->prawe);
}

treap* zlacz(treap *a, treap *b)
{
  if (!a) return b;
  if (!b) return a;
  a -> propaguj();
  b -> propaguj();
  if (a->rank > b->rank)
  {
    a->prawe = zlacz(a->prawe, b);
    a->prawe->rodzic = a;
    policz_rozmiar(a);
    return a;
  }
  else
  {
    b->lewe = zlacz(a, b->lewe);
    b->lewe->rodzic = b;
    policz_rozmiar(b);
    return b;
  }
}

pair<treap*, treap*> rozdziel(treap* a, int k)
{
  if (!a) return {0, 0};
  if (k == 0) return {0, a};
  if (k == rozmiar(a)) return {a, 0};
  a -> propaguj();
  if (rozmiar(a->lewe) >= k)
  {
    auto x = rozdziel(a->lewe, k);
    a->lewe = x.second;
    policz_rozmiar(a);
    x.second->rodzic = a;
    return {x.first, a};
  }
  else
  {
    auto x = rozdziel(a->prawe, k-rozmiar(a->lewe)-1);
    a->prawe = x.first;
    policz_rozmiar(a);
    x.first->rodzic = a;
    return {a, x.second};
  }
}

treap* odwroc_funkcja(treap *v, int a, int b)
{
  auto x = rozdziel(v, a-1);
  auto y = rozdziel(x.second, b-a+1);
  if (y.first)
    y.first->odwroc = true;
  return zlacz(x.first, zlacz(y.first, y.second));
}

void propaguj_gore(treap *a)
{
  if (!a) return;
  propaguj_gore(a->rodzic);
  a->propaguj();
}

int ktory(treap *a)
{
  if (!a->rodzic) return rozmiar(a->lewe) + 1;
  if (a->rodzic->prawe == a)
  {
    return ktory(a->rodzic) + rozmiar(a->lewe) + 1;
  }
  else
  {
    return ktory(a->rodzic) - rozmiar(a->prawe) - 1;
  }
}

const int N = 3e5 + 5;
int n;
vector<treap*> wier;

int main()
{
  treap *root(0);
  wier.push_back(root);
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) 
  {
    int a; scanf("%d", &a);
    wier.push_back(new treap(a));
    root = zlacz(root, wier.back());
  }
  
  for (int i = 1; i <= n; i++)
  {
    treap *a = wier[i];
    propaguj_gore(a);
    int x = ktory(a);
    printf("%d ", x);
    root = odwroc_funkcja(root, i+1, x);
  }
  printf("\n");
  
	return 0;
}
