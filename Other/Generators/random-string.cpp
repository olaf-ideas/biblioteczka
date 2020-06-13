#include <bits/stdc++.h>
using namespace std;
const int MINN = 100000, MAXN = 1000000;

template<class T>T rand(T a, T b){return T(a+rand()%(b-a+1));}

int main(int argc, char *argv[]){
  (argc > 1 ? srand(atoi(argv[1])) : srand(int(time(NULL))));
  ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);

  int n = rand(MINN,MAXN);
  cout << n << "\n";
  for(int i = 0; i < n; i++)
    cout << rand('a', 'z');
  cout << "\n";
}