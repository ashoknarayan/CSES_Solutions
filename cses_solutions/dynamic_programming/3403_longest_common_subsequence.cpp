#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int& x : a) cin >> x;
    for (int& x : b) cin >> x;

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Fill dp table
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

    // Traceback to get one LCS
    int i = n, j = m;
    vector<int> lcs;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            lcs.push_back(a[i - 1]);
            --i, --j;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    reverse(lcs.begin(), lcs.end());

    cout << lcs.size() << endl;
    for (int x : lcs)
        cout << x << " ";
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}
