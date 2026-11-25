#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    unordered_map<int, int> freq;
    set<int> mex_candidates;

    for (int i = 0; i <= n; ++i) mex_candidates.insert(i); // Pre-fill with [0..n]

    // Initialize first window
    for (int i = 0; i < k; ++i) {
        freq[a[i]]++;
        mex_candidates.erase(a[i]);
    }

    cout << *mex_candidates.begin() << ' ';

    // Slide the window
    for (int i = k; i < n; ++i) {
        int out = a[i - k];
        int in = a[i];

        // Remove outgoing element
        if (--freq[out] == 0) {
            freq.erase(out);
            if (out <= n) mex_candidates.insert(out);
        }

        // Add incoming element
        freq[in]++;
        if (freq[in] == 1 && in <= n)
            mex_candidates.erase(in);

        cout << *mex_candidates.begin() << ' ';
    }

    cout << endl;
}
