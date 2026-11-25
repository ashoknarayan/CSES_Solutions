#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int minA = 1e18, maxA = -1e18;
    int minB = 1e18, maxB = -1e18;

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;

        int A = x + y;
        int B = x - y;

        minA = min(minA, A);
        maxA = max(maxA, A);
        minB = min(minB, B);
        maxB = max(maxB, B);

        int max_dist = max(maxA - minA, maxB - minB);
        cout << max_dist << endl;
    }

    return 0;
}
