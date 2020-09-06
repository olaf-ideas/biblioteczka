// olaf_surgut
//        _        __                             _   
//   ___ | | __ _ / _|  ___ _   _ _ __ __ _ _   _| |_ 
//  / _ \| |/ _` | |_  / __| | | | '__/ _` | | | | __|
// | (_) | | (_| |  _| \__ \ |_| | | | (_| | |_| | |_ 
//  \___/|_|\__,_|_|___|___/\__,_|_|  \__, |\__,_|\__|
//                |_____|             |___/           
//
#include <bits/stdc++.h>

using namespace std;

typedef long long int LL;
typedef long double LD;

const int INF = 1e9 + 7;
const LL LONG_INF = 1e18 + 7;
const LD EPS = 1e-9;

template <class T> inline T rd() {
    T r=0; int c = getchar();
    while(c < '0' || c > '9')   c = getchar();
    for(; '0' <= c && c <= '9'; c = getchar())
        r = (r << 3) + (r << 1) + c - 48;
    return r;
}

int main() {
}
