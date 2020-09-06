const int MAXD = 24;

constexpr int count(int n, int depth=1){
  return depth == MAXD ? n + 1: count(count(n, depth + 1), depth + 1) + 1;
}

#include<iostream>

int main(){
  constexpr int i = count(0);
  std::cout << i << std::endl;
}
