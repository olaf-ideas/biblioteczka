#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++){
        int n, k;
        cin >> n >> k;
        int ans = 0, now = k;
        for(int i = 0; i < n; i++){
            int a; cin >> a;
            if(a == now)    now--;
            else            now = k;
            if(now == 0)    ans++, now = k;
        }
        cout << "Case #" << _ << ": " << ans << '\n';
    }       
}
