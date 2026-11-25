#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9 + 7;

int modmul(int a, int b) {
    return (a * b) % MOD;
}

void solve() {
    int n;
    cin >> n;
    map<int, int> freq;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        freq[x]++;
    }

    int res = 1;
    for (auto [val, cnt] : freq) {
        res = modmul(res, cnt + 1);  // each element can be used in (cnt + 1) ways (including not picking it)
    }

    res = (res - 1 + MOD) % MOD;  // remove empty subsequence
    cout << res << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}
