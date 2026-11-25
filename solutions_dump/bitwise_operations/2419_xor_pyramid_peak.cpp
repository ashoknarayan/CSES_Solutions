#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    int ans = 0;
    int mask = n - 1;

    for (int i = 0; i < n; i++) {
        // Check parity of C(n-1, i)
        if ((i & mask) == i) {
            ans ^= a[i];
        }
    }

    cout << ans << "\n";

    return 0;
}
