const int N = 100000005, SQRT = 31625;

bitset<N> s;
vector<int> primes;

void sieve(){
  for(int i = 2; i <= SQRT; i++){
    if(!s[i]){
      primes.push_back(i);
      for(int j = i*i; j < N; j += i)
        s[j] = true;
    }
  }
  for(int i = SQRT+1; i < N; i++)
    if(!s[i]) primes.push_back(i);
}