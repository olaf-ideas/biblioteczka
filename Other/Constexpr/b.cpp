constexpr bool rec_isprime(unsigned long n, unsigned long div){
  return n % div == 0 ?
           false
         : (div * div > n ? true : rec_isprime(n, div + 2));
}

constexpr bool isprime(unsigned long n){
  return n == 2 or n == 3 or (n % 2 and rec_isprime(n, 3));
}

#include<iostream>

int main(){
  //constexpr in declaration guarantees that it is evaluated compile time
  constexpr bool p1 = isprime(1 << 23);
  constexpr bool p2 = isprime((1 << 20) - 1);
  std::cout << p1 << " " << p2 << std::endl;
}
