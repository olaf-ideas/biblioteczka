#include <bits/stdc++.h>
using namespace std;

int main(){
  const int n = 10000;
  long long sum = 0;
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
      sum += gcd(i, j);
  printf("%lld\n", sum);
}
