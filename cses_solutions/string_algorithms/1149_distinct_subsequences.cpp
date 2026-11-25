#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int MOD = 1e9 + 7;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    vector<int> dp(n + 1); // dp[i] = #distinct subsequences using first i characters
    dp[0] = 1; // base: empty subsequence

    vector<int> last(26, -1); // last occurrence of each character

    for (int i = 0; i < n; ++i) {
        dp[i + 1] = (2 * dp[i]) % MOD;

        int ch = s[i] - 'a';
        if (last[ch] != -1) {
            dp[i + 1] = (dp[i + 1] - dp[last[ch]] + MOD) % MOD;
        }

        last[ch] = i;
    }

    // subtract 1 to exclude the empty subsequence
    cout << (dp[n] - 1 + MOD) % MOD << endl;
}
