#include <bits/stdc++.h>
using namespace std;

namespace treap {

struct Node {       // wezel struktury
    int key;        // klucz przechowywany w wezle (informacja) - struktura jest BST wzgledem kluczy
    int priority;   // losowy priorytet dla zachowania balansu drzewa - struktura jest kopcem typu max wzgledem priorytetow
    Node* left;     // wskaznik na lewe poddrzewo
    Node* right;    // wskaznik na prawe poddrzewo

    Node() { key = -1; priority = -1; left = nullptr; right = nullptr; }
    Node(int k, int p) { key = k; priority = p; left = nullptr; right = nullptr; }
};

typedef Node* PtrNode;    // typ danych (wskaznik na wezel)

void split(PtrNode T, int key, PtrNode& l, PtrNode& r) {
    // funkcja bierze strukture T i rozbija ja na dwie struktury l oraz r wzgledem klucza key
    // mniejsze wartosci ida do l, wieksze lub rowne do r

    if (T == nullptr) { l = nullptr; r = nullptr; return; }
    if (key < T->key) { split(T->left, key, l, T->left); r = T; }
    else { split(T->right, key, T->right, r); l = T; }  
}

void meld(PtrNode& T, PtrNode l, PtrNode r) {
    // funkcja bierze struktury l i r (zakladamy ze wszystkie klucze w l sa mniejsze niz wszystkie klucze w t) i skleja je do struktury T

    if (l == nullptr) { T = r; return; }
    if (r == nullptr) { T = l; return; }
    if (l->priority > r->priority) { meld(l->right, l->right, r); T = l; }
    else { meld(r->left, l, r->left); T = r; }
}

void insert(PtrNode& T, PtrNode it) {
    // funkcja dodaje wezel it do struktury T
    // TODO: zaimplementuj
    meld(T, it);
}

void insert(PtrNode& T, int key) {
    // funkcja dodaje wezel o kluczu key do struktury T

    int priority = rand();
    PtrNode it = new Node(key, priority);
    insert(T, it);
}

void erase(PtrNode& T, int key) {
    // funkcja usuwa wezel o kluczu key ze struktury T
    // TODO: zaimplementuj
    PtrNode l, r;
    split(T, key, l, r);
    meld(r->left, r->left, r->right);
    meld(l, l, r->left);
    T = l;
}

void items(PtrNode& T) {
    // funkcja wypisuje kolejne elementy T

    if (T == nullptr) return;

    items(T->left);
    cout << T->key << " ";
    items(T->right);
}

};

int main() {
    treap::PtrNode root = nullptr;

    while (true) {
        string op;
        cin >> op;

        if (op == "insert") {
            int x;
            cin >> x;
            treap::insert(root, x);
        }

        if (op == "erase") {
            int x;
            cin >> x;
            treap::erase(root, x);
        }

        if (op == "print") {
            treap::items(root);
            cout << "\n";
        }
    }


    return 0;
}
