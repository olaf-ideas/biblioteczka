vector<int> factor(int n){  // O(sqrt(N))
  vector<int> r;
  for(int i = 2; i * 1LL * i <= n; i++)
    while(n % i == 0) r.push_back(i), n /= i;
  if(n > 1) r.push_back(n);
  return r;
}