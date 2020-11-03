#include <bits/stdc++.h>

using namespace std;

template <size_t S>
struct Knapsack {
    bitset<S> dp;
    int nx[S];

    void add_coin(int coin) {
        bitset<S> x = dp;
        dp |= dp << coin;
        x ^= dp;
        for(int i = x._Find_first(); i < (int) S; i = x._Find_next(i))
            nx[i] = coin; 
    }

    bool can(int value) { return dp[value]; }

    vector<int> get_change(int value) {
        vector<int> res;
        while(value > 0) {
            res.push_back(nx[value]);
            value -= nx[value];
        }
        return res;
    }
};


int main() {
}
