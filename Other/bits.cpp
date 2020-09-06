#include <bits/stdc++.h>

using namespace std;

// lexicographically next bit permutation
inline bool next_permutation_bits(unsigned int &v) {
  if(ffs(v) == 33 - __builtin_popcount(v)) return false;
  unsigned int t = v | (v - 1);
  v = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));
  return true;
}

#define MAX(x, y) x ^ ((x ^ y) & -(x < y))  // max(x, y)
#define MIN(x, y) y ^ ((x ^ y) & -(x < y))  // min(x, y)

// check if x is 2^x
inline bool power_of_two(unsigned x) {
  return !(x & (x - 1));
}

int main() {
  unsigned int x = 1;
  cin >> x;

  do
    cout << bitset<32>(x) << '\n';
  while(next_permutation_bits(x));

  __builtin_popcount(x);  // number of set bits
  __builtin_parity(x);    // 1 if number of set bits is odd, 0 otherwise = (__builtin_popcount(x) & 1)
  __builtin_clz(x);       // number of leading zero's
  __builtin_ctz(x);       // number of trailing zero's
}
