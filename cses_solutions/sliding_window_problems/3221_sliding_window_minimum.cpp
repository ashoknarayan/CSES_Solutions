#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    int x, a, b, c;
    cin >> x >> a >> b >> c;

    deque<pair<int, int>> dq; // (value, index)
    int xor_sum = 0;

    int curr = x;

    for (int i = 0; i < n; ++i) {
        // Remove from back while elements ≥ curr
        while (!dq.empty() && dq.back().first >= curr)
            dq.pop_back();

        dq.emplace_back(curr, i);

        // Remove front if out of window
        if (!dq.empty() && dq.front().second <= i - k)
            dq.pop_front();

        if (i >= k - 1)
            xor_sum ^= dq.front().first;

        // Generate next element
        curr = (a * curr + b) % c;
    }

    cout << xor_sum << endl;
    return 0;
}
