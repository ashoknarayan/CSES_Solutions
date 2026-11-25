#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int MAX_K = 1e7 + 5;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    int x, a, b, c;
    cin >> x >> a >> b >> c;

    queue<int> q;
    int sum = 0, xor_sum = 0;
    int curr = x;

    for (int i = 1; i <= n; ++i) {
        sum += curr;
        q.push(curr);

        if (q.size() > k) {
            sum -= q.front();
            q.pop();
        }

        if (i >= k)
            xor_sum ^= sum;

        // Generate next element
        curr = (a * curr + b) % c;
    }

    cout << xor_sum << endl;
    return 0;
}
