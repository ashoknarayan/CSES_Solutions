#include <bits/stdc++.h>
using namespace std;

int n, k;
string grid[3000];
int dp[3000][3000];
int64_t result[26];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < n; ++i)
        cin >> grid[i];

    for (int ch = 0; ch < k; ++ch) {
        char target = 'A' + ch;

        // Clear DP array (only needed for first row)
        for (int i = 0; i < n; ++i)
            dp[0][i] = (grid[0][i] == target ? 1 : 0);
        for (int i = 1; i < n; ++i)
            dp[i][0] = (grid[i][0] == target ? 1 : 0);

        // Count 1st row and col
        for (int i = 0; i < n; ++i)
            result[ch] += dp[0][i];
        for (int i = 1; i < n; ++i)
            result[ch] += dp[i][0];

        // Main DP loop
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < n; ++j) {
                if (grid[i][j] == target) {
                    dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
                    result[ch] += dp[i][j];
                } else {
                    dp[i][j] = 0;
                }
            }
        }
    }

    for (int ch = 0; ch < k; ++ch)
        cout << result[ch] << '\n';

    return 0;
}
