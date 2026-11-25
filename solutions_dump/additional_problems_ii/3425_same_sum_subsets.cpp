#include <algorithm>
#include <cstring>
#include <iostream>
#define SZ(X) (int)(X).size()
using namespace std;
using ll = long long;
const int AA = 19;
ll a[40];
ll dp[41][1 << AA];
ll res[1 << (40 - AA)];
int b, p, mask;
void print(ll v) {
    cout << __builtin_popcountll(v) << '\n';
    for (int i = 0; i < 40; i++) {
        if ((v >> i) & 1) cout << a[i] << ' ';
    }
    cout << '\n';
}
void dfs(int i, int x, ll use, ll sum) {
    if (!i) {
        if (res[sum >> b]) {
            ll v = res[sum >> b];
            ll same = use & v;
            v ^= same;
            use ^= same;
            print(v);
            print(use);
            exit(0);
        }
        res[sum >> b] = use;
        return;
    }
    if (dp[i - 1][x]) dfs(i - 1, x, use, sum);
    if (dp[i - 1][(x - a[i - 1]) & mask]) dfs(i - 1, (x - a[i - 1]) & mask, use | (1ll << i - 1), sum + a[i - 1]);
}
int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    b = min(n / 2, AA);
    p = 1 << b;
    mask = p - 1;
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        memcpy(dp[i + 1], dp[i], sizeof(dp[i]));
        for (int j = 0; j < p; j++) {
            if (!dp[i][j]) continue;
            dp[i + 1][(j + a[i]) & mask] += dp[i][j];
        }
    }
    for (int i = 0; i < p; i++) {
        if (dp[n][i] > (1ll << n) / p || i == p - 1) {
            dfs(n, i, 0, 0);
        }
    }
}
