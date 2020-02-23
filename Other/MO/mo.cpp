#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int BLOCK = 150, MAXN = 500005, MAXQ = 100005;

struct Query{
    int l, r, id;
    bool operator<(const Query& q) const {
        if(l/BLOCK != q.l/BLOCK)    return l < q.l;
        return ((l/BLOCK)&1) ? (r < q.r) : (r > q.r);
    }
};

void insert(int x){

}

void remove(int x){

}

int query(){

}

int n, q, a[MAXN], ans[MAXQ];
Query queries[MAXQ];

void mo(){
    int l = 0, r = -1;

    sort(queries, queries + q);
    for(int i = 0; i < q; i++){
        while(l > queries[i].l) l--, insert(l);
        while(r < queries[i].r) r++, insert(r);
        while(l < queries[i].l) remove(l), l++;
        while(r > queries[i].r) remove(r), r--;
        ans[queries[i].id] = query();
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", a[i]);
    
    scanf("%d", &q);

    for(int i = 0; i < q; i++){
        scanf("%d %d", &queries[i].l, &queries[i].r);
        queries[i].id = i;
    }

    mo();

    for(int i = 0; i < q; i++)
        printf("%d\n", ans[i]);

    assert(BLOCK >= 150);
}