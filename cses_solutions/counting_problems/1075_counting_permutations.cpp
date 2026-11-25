#include <stdio.h>
typedef long long ll;
const int N = 1001;
const ll MOD = 1e9+7;
int main() {
    ll dp[N];
    dp[0] = dp[1] = 1; dp[2] = dp[3] = 0;
    for (int i = 4; i<N; ++i) {
        dp[i] = (i+1)*dp[i-1] - (i-2)*dp[i-2]
                - (i-5)*dp[i-3] + (i-3)*dp[i-4];
        dp[i] %= MOD;
        dp[i] = (dp[i]+MOD)%MOD;
    }
    ll n;
    scanf("%lld", &n);
    printf("%lld", dp[n]);
}
