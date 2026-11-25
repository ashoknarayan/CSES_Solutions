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

    queue<int> q;
    int window_xor = 0, total_xor = 0;
    int curr = x;

    for (int i = 1; i <= n; ++i) {
        window_xor ^= curr;
        q.push(curr);

        if ((int)q.size() > k) {
            window_xor ^= q.front();
            q.pop();
        }

        if (i >= k)
            total_xor ^= window_xor;

        // Generate next element
        curr = (a * curr + b) % c;
    }

    cout << total_xor << endl;
    return 0;
}
