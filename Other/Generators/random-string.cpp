#include <bits/stdc++.h>
using namespace std;

int N = 1e5;

template<class T> inline T r(T a, T b) { return T(a + rand() % (b - a + 1)); }

int main(int argc, char* argv[]){
  srand(atoi(argv[1]));

  int n = r(1, N);
  printf("%d\n", n);
  for(int i = 0; i < n; i++)  printf("%c", r('a', 'z'));
  printf("\n");
}