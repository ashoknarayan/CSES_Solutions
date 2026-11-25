#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int N = 5005;

int dp[N][N];

void solve() {
    int n;
    cin >> n;

    dp[1][0] = 1; // 1 element, 0 breakpoints

    for (int i = 2; i <= n; i++) {
        for (int k = 0; k < i; k++) {
            // recurrence for Eulerian numbers
            dp[i][k] = ((i - k) * dp[i - 1][k - 1] % MOD + (k + 1) * dp[i - 1][k] % MOD) % MOD;
        }
    }

    for (int r = 1; r <= n; r++) {
        cout << dp[n][r - 1] << " ";
    }
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
