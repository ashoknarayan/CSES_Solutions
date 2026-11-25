#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll lcm(ll a, ll b) {
    return a / __gcd(a, b) * b;
}

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;

    if (k == 0) {
        cout << "1 1 0\n";
        return;
    }

    ll N = n - 1, M = m - 1;

    ll x = (k % (2 * N) < N) ? 1 + k % (2 * N) : n - (k % (2 * N) - N);
    ll y = (k % (2 * M) < M) ? 1 + k % (2 * M) : m - (k % (2 * M) - M);

    ll changes = k / N + k / M - k / lcm(N, M);
    cout << x << " " << y << " " << changes << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
