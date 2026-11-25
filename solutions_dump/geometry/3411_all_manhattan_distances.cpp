#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define endl '\n'

// Safely compute Manhattan sum using __int128 to avoid overflow
__int128 compute_sum(vector<int>& a) {
    sort(a.begin(), a.end());
    __int128 total = 0, prefix = 0;
    for (int i = 0; i < a.size(); ++i) {
        total += (__int128)a[i] * i - prefix;
        prefix += a[i];
    }
    return total;
}

// Print __int128 properly
void print128(__int128 x) {
    if (x == 0) {
        cout << 0;
        return;
    }
    string s;
    bool neg = false;
    if (x < 0) {
        neg = true;
        x = -x;
    }
    while (x > 0) {
        s += '0' + x % 10;
        x /= 10;
    }
    if (neg) cout << '-';
    reverse(s.begin(), s.end());
    cout << s;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }

    __int128 total = compute_sum(x) + compute_sum(y);
    print128(total);
    cout << endl;

    return 0;
}
