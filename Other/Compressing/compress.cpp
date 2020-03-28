#include <bits/stdc++.h>
using namespace std;

vector<int> compress(vector<int> a){
    vector<int> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for(int &x : a) x = int(lower_bound(b.begin(), b.end(), x)-b.begin());
    return a;
}

int main(){
    return 0;
}