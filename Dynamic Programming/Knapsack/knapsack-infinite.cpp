#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10005, MAXC = 105, INF = 1000000005;

int n, m, dp[MAXN], last[MAXN], coins[MAXC];

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++)  scanf("%d", &coins[i]);

    fill(dp,dp+MAXN,INF);
    dp[0] = 0;
    for(int i = 1; i <= m; i++){
        for(int j = 0; j < n; j++){
            if(i-coins[j] >= 0 && dp[i] > dp[i-coins[j]]+1){
                dp[i] = dp[i-coins[j]]+1;
                last[i] = coins[j];
            }
        }
    }
    printf("used: %d\n", dp[m]);
    printf("coins: ");
    while(m > 0){
        printf("%d ", last[m]);
        m -= last[m];
    }
    printf("\n");
}