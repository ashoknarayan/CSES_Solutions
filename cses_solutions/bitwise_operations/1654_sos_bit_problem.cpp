#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int &x : a)
        cin >> x;

    vector<int> dp(1 << 20), kp(1 << 20);


    for (int x : a) 
        dp[x]++, kp[x]++;

    for (int i=0; i<20; ++i)
        for (int mask=0; mask<(1<<20); ++mask)
            if (mask & (1<<i))
                dp[mask] += dp[mask ^ (1 << i)];
            else
                kp[mask] += kp[mask ^ (1 << i)];

    for (int x:a) {
        cout << dp[x] << ' '
             << kp[x] << ' '
             << n - dp[((1 << 20) - 1) ^ x] << '\n';
    }

    return 0;
}
