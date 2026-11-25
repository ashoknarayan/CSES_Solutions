#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    set<int> s;
    int ans = 0, l = 0;

    for (int r = 0; r < n; ++r) {
        while (s.count(a[r])) {
            s.erase(a[l]);
            ++l;
        }
        s.insert(a[r]);
        ans += (r - l + 1);
    }

    cout << ans << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
