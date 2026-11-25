#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    unordered_map<int, int> pos;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        pos[a[i]] = i;
    }

    vector<int> seq;
    vector<int> orig_vals;  // to retrieve the original values
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
        if (pos.count(b[i])) {
            seq.push_back(pos[b[i]]);
            orig_vals.push_back(b[i]);
        }
    }

    // Find LIS on `seq`
    vector<int> dp, idx(seq.size()), parent(seq.size(), -1);

    for (int i = 0; i < seq.size(); ++i) {
        int x = seq[i];
        auto it = lower_bound(dp.begin(), dp.end(), x);
        int pos = it - dp.begin();
        if (it == dp.end()) dp.push_back(x);
        else *it = x;
        idx[pos] = i;
        if (pos > 0) parent[i] = idx[pos - 1];
    }

    // Reconstruct LIS
    int len = dp.size();
    vector<int> result;
    int i = idx[len - 1];
    while (i != -1) {
        result.push_back(orig_vals[i]);
        i = parent[i];
    }

    reverse(result.begin(), result.end());

    cout << len << endl;
    for (int x : result) cout << x << " ";
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}
