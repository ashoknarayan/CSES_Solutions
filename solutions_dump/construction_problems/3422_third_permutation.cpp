#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n), c(n);
    for (int &x : a) cin >> x;
    for (int &x : b) cin >> x;

    // Start with a rotated version of a
    for (int i = 0; i < n; ++i) {
        c[i] = a[(i + 1) % n];
    }

    // Fix conflicts
    for (int i = 0; i < n; ++i) {
        if (c[i] == a[i] || c[i] == b[i]) {
            for (int j = 0; j < n; ++j) {
                if (j != i &&
                    c[j] != a[i] && c[j] != b[i] &&
                    c[i] != a[j] && c[i] != b[j]) {
                    swap(c[i], c[j]);
                    break;
                }
            }
        }
    }

    // Final check
    for (int i = 0; i < n; ++i) {
        if (c[i] == a[i] || c[i] == b[i]) {
            cout << "IMPOSSIBLE" << endl;
            return;
        }
    }

    for (int x : c) cout << x << ' ';
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
