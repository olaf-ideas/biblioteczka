#include "../../string/kmp.h"

#include <bits/stdc++.h>

using namespace std;

int rand(int a, int b) { return a + rand() % (b - a + 1); }

vector<int> brute(const string &s, const string &t) {
    vector<int> r;
    for(int i = 0; i < (int) (t.size() - s.size()) + 1; i++) {
        if(s == t.substr(i, s.size()))  r.push_back(i);
    }
    return r;
}

int main(int argc, char**argv) {
    srand(atoi(argv[1]));
    for(int rep = 0; rep < 2e6; rep++) {
        string s, t;
        int n = rand(1, 10);
        for(int i = 0; i < n; i++)  s += char(rand('a', 'z'));
        int m = rand(8, 100);
        for(int i = 0; i < m; i++)  t += char(rand('a', 'z'));
       
        if(kmp(s, t) != brute(s, t)) {
            cout << s << ' ' << t << '\n';
            assert(false);
        }

    }
}
