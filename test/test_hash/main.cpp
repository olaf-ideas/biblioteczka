#include "../../string/hash.h"

#include <bits/stdc++.h>

using namespace std;

string s;

int main() {
    for(char c = '0'; c <= '9'; c++)    cout << to_int(c) << ' ';
    for(char c = 'a'; c <= 'z'; c++)    cout << to_int(c) << ' ';
    for(char c = 'A'; c <= 'Z'; c++)    cout << to_int(c) << ' ';
    cout << '\n';

    cin >> s;

    hash64 h(s);

    cout << h.get(0, (int) s.size()) << '\n';
}

