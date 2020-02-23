#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 200005, MAXM = 200005, MAXC = 1000000005;

int rand(int a, int b){return a+rand()%(b-a+1);}

int main(int argc, char *argv[]){
    srand(atoi(argv[1]));

    set<pair<int,int>> edges;
    int n = rand(1,MAXN), m = rand(1,min(MAXM,(n*(n-1))>>1));
    
    printf("%lld %lld\n", n, m);
    
    for(int i = 0; i < m; i++){
        int a = rand(1,n), b = rand(1,n);

        while(a == b || edges.count(make_pair(a,b)) || 
                        edges.count(make_pair(b,a)))
            a = 1+rand()%n, b = 1+rand()%n;
        
        edges.insert(make_pair(a,b));
    }

    for(const pair<int,int> &edge : edges)
        printf("%d %d %d\n", edge.first, edge.second, rand(1,MAXC));
}