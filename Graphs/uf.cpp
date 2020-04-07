const int N = 100005;

int uf[N];

void build_uf(){for(int i=0;i<N;i++)uf[i]=i;}
int find_uf(int u){return uf[u]==u?u:uf[u]=find_uf(uf[u]);}
void union_uf(int u, int v){uf[find_uf(u)]=uf[find_uf(v)];}