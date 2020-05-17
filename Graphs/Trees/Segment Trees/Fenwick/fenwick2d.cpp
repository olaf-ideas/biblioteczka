// Fenwick tree 2D update: O(log^2 n), query: O(log^2 n)

const int N = 5005;

int t[N][N];

void update(int x, int y, int v){
  for(; x < N; x += x & -x)
    for(int yy = y; yy < N; yy += yy & -yy)
      t[x][yy] += v;
}

int query(int x, int y){
  int r = 0;
  for(; x > 0; x -= x & -x)
    for(int yy = y; yy > 0; yy -= yy & -yy)
      r += t[x][yy];
  return r;
}