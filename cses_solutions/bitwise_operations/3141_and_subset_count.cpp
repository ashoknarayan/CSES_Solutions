#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9 + 7;

int power(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n; cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    
    int max_val = n;
    int size = 1;
    while (size <= max_val) size <<= 1;

    vector<int> freq(size, 0);
    for (int x : a) freq[x]++;
    
    // Fast Zeta Transform on AND
    vector<int> superset_cnt = freq;
    for (int i = 0; i < __lg(size); ++i) {
        for (int mask = 0; mask < size; ++mask) {
            if ((mask & (1 << i)) == 0)
                superset_cnt[mask] += superset_cnt[mask | (1 << i)];
        }
    }

    vector<int> dp(size, 0);
    for (int mask = 0; mask <= max_val; ++mask) {
        if (superset_cnt[mask] == 0) continue;
        dp[mask] = (power(2, superset_cnt[mask]) - 1 + MOD) % MOD;
    }

    // Möbius Inversion on AND
    for (int i = 0; i < __lg(size); ++i) {
        for (int mask = 0; mask < size; ++mask) {
            if ((mask & (1 << i)) == 0)
                dp[mask] = (dp[mask] - dp[mask | (1 << i)] + MOD) % MOD;
        }
    }

    for (int k = 0; k <= n; ++k)
        cout << dp[k] << " ";
    cout << endl;
}
