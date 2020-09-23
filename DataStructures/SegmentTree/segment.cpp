#include <bits/stdc++.h>

using namespace std;

class SegmentTree {
public:
    struct Node {
        long long a = 0;
        int p = 0;
        void apply(int l, int r, int v) {
            p += v;
        }
    };

    Node unite(const Node &a, const Node &b) const {
        Node res;
        res.a = a.a + b.a;
        return res;
    }

    void push(int x, int l, int r) {
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        // push from x into (x + 1) and z
        if(tree[x].p != 0) {
            cerr << "PUSH: " << x << "\n";
            tree[x].a += (long long) tree[x].p * (r - l + 1);

            tree[x + 1].apply(l, y, tree[x].p);
            tree[z].apply(y + 1, r, tree[x].p);

            tree[x].p = 0;
        }
    }

    void pull(int x, int z) {
        tree[x] = unite(tree[x + 1], tree[z]); 
    }
    
    int n;
    vector<Node> tree;
    
    void build(int x, int l, int r) {
        if(l == r)  return;
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r);
        build(x + 1, l, y);
        build(z, y + 1, r);
        pull(x, z);
    }

    template <typename M>
    void build(int x, int l, int r, const vector<M> &v) {
        if(l == r) {
            tree[x].apply(l, r, v[l]);
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r);
        build(x + 1, l, y, v);
        build(z, y + 1, r, v);
        pull(x, z);
    }

    Node get(int x, int l, int r, int ll, int rr) {
        if(ll <= l && r <= rr) {
            return tree[x];
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r);
        Node res{};
        if(rr <= y)     res = get(x + 1, l, y, ll, rr);
        else if(ll > y) res = get(z, y + 1, r, ll, rr);
        else            res = unite(get(x + 1, l, y, ll, rr), get(z, y + 1, r, ll, rr));
        pull(x, z);
        return res;
    }

    template <typename... M>
    void modify(int x, int l, int r, int ll, int rr, const M&... v) {
        if(ll <= l && r <= rr) {
            cerr << x << " APPLY: " << '\n';
            tree[x].apply(l, r, v...);
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r);
        if(ll <= y) modify(x + 1, l, y, ll, rr, v...);
        if(rr > y)  modify(z, y + 1, r, ll, rr, v...);
        pull(x, z);
    }

    SegmentTree(int _n) : n(_n) {
        assert(n > 0);
        tree.resize(2 * n - 1);
        build(0, 0, n - 1);
    }

    template <typename M>
    SegmentTree(const vector<M> &v) : n((int) v.size()) {
        tree.resize(2 * n - 1);
        build(0, 0, n - 1, v);
    }

    Node get(int ll, int rr) {
        assert(0 <= ll && ll <= rr && rr <= n - 1);
        return get(0, 0, n - 1, ll, rr);
    }

    Node get(int p) {
        assert(0 <= p && p <= n - 1);
        return get(0, 0, n - 1, p, p);
    }
    
    template <typename... M>
    void modify(int ll, int rr, const M&... v) {
        assert(0 <= ll && ll <= rr && rr <= n - 1);
        modify(0, 0, n - 1, ll, rr, v...);
    }
};

struct Brute {
    vector<long long> tree;
    
    Brute(int n) : tree(n, 0) { }

    void add(int l, int r, int v) {
        for(int i = l; i <= r; i++) tree[i] += v;
    }

    long long query(int l, int r) {
        long long res = 0;
        for(int i = l; i <= r; i++) res += tree[i];
        return res;
    }
};

int rand(int l, int r) { return l + rand() % (r - l + 1); }

int main(int argc, char *argv[]) {
    srand(atoi(argv[1]));

    int n = rand(1, 10);

    SegmentTree sg(n);
    Brute bt(n);

    for(int i = 0; i < 100; i++) {
        int l = rand(0, n); 
        int r = rand(l, n - 1);
        int v = rand(0, 10);
     
        if(rand() & 1) {
            sg.modify(l, r, v);
            bt.add(l, r, v);
            cerr << "UPDATE: " << l << ' ' << r << ' ' << v << '\n';;
        } else {
            cerr << "p: ";
            for(auto x : sg.tree)    cerr << x.a << ',' << x.p << ' ';
            cerr << '\n';
        
            cerr << "QUERY: " << l << ' ' << r << " segment: " << sg.get(l, r).a << " brute: " << bt.query(l, r) << '\n';
            assert(sg.get(l, r).a == bt.query(l, r));
        }
    }
}
