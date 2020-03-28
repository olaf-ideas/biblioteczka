#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005, SQRT = 1001;

bool s[MAXN];
vector<int> primes;

void sieve(){
    for(int i = 2; i <= SQRT; i++){
        if(!s[i]){
            primes.push_back(i);
            for(int j = i*i; j < MAXN; j += i)
                s[j] = true;
        }
    }
    for(int i = SQRT+1; i < MAXN; i++)
        if(!s[i])   primes.push_back(i);
}

int main(){
    sieve();
    for(int p : primes)
        cout << p << ", ";
    cout << "\n";
}