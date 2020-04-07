#include <bits/stdc++.h>
using namespace std;
const int MINN = 100005, MAXN = 1000005;

int rand(int a, int b){return a+rand()%(b-a+1);}

int main(int argc, char *argv[]){
  srand(atoi(argv[1]));
  ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);

  int n = rand(MINN,MAXN);
  
  cout << n << "\n";
  for(int i = 0; i < n; i++)
    cout << char(rand('a', 'z'));
  cout << "\n";
}