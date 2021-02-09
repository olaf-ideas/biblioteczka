#include "../../string/manacher.h"

#include <bits/stdc++.h>

using namespace std;

vector<int> brute_even(const string &s) {
    vector<int> r((int) s.size());
    for(int i = 0; i < (int) s.size() - 1; i++) {
        int j = 0;
        while(i - j >= 0 && 
              i + j + 1 < (int) s.size() && 
              s[i - j] == s[i + j + 1])
            j++;
        r[i] = j;
    }
    return r;
}

vector<int> brute_odd(const string &s) {
    vector<int> r((int) s.size());
    for(int i = 0; i < (int) s.size(); i++) {
        int j = 0;
        while(i - j - 1 >= 0 && 
              i + j + 1 < (int) s.size() && 
              s[i - j - 1] == s[i + j + 1])
            j++;
        r[i] = j;
    }
    return r;
}

int rand(int a, int b) { return a + rand() % (b - a + 1); }

int main(int argc, char**argv) {
    srand(atoi(argv[1]));
    for(int rep = 0; rep < 2e6; rep++) {
        string s;
        int n = rand(1, 10000);
        for(int i = 0; i < n; i++)  s += char(rand('a', 'z'));

        assert(brute_even(s) == manacher_even(s));
        assert(brute_odd(s) == manacher_odd(s));
    }
}
