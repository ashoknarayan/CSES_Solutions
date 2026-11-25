#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

void solve() {
    int n;
    cin >> n;
    vector<int> sa(n);
    for (int i = 0; i < n; ++i) {
        cin >> sa[i];
        --sa[i]; // convert to 0-based
    }

    if (n == 1) {
        cout << 'a' << endl;
        return;
    }

    // Build rank array
    vector<int> rank(n);
    for (int i = 0; i < n; ++i)
        rank[sa[i]] = i;

    vector<int> s(n, 'a');

    for (int i = 1; i < n; ++i) {
        int prev_pos = sa[i - 1];
        int curr_pos = sa[i];

        if (prev_pos + 1 < n && curr_pos + 1 < n) {
            if (rank[prev_pos + 1] > rank[curr_pos + 1]) {
                if (s[prev_pos] >= s[curr_pos])
                    s[curr_pos] = s[prev_pos] + 1;
            } else {
                if (s[prev_pos] > s[curr_pos])
                    s[curr_pos] = s[prev_pos];
            }
        } else {
            if (prev_pos + 1 >= n && curr_pos + 1 >= n) {
                if (s[prev_pos] > s[curr_pos])
                    s[curr_pos] = s[prev_pos];
            } else if (prev_pos + 1 >= n) {
                if (s[prev_pos] > s[curr_pos])
                    s[curr_pos] = s[prev_pos];
            } else {
                if (s[prev_pos] >= s[curr_pos])
                    s[curr_pos] = s[prev_pos] + 1;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (s[i] > 'z') {
            cout << -1 << endl;
            return;
        }
    }

    for (int i = 0; i < n; ++i)
        cout << (char)s[i];
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}
