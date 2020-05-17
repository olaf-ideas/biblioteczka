const int N = 1000005;

int uf[N];

int  f(int x){return uf[x] == x ? x : uf[x] = f(uf[x]);}
void u(int x, int y){uf[f(x)] = uf[f(y)];}