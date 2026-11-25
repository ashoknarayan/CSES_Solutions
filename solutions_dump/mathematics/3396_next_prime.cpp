#include <bits/stdc++.h>
using namespace std;
#define int long long

int mulmod(int a, int b, int mod) {
    int result = 0;
    a %= mod;
    while (b) {
        if (b & 1)
            result = (result + a) % mod;
        a = (2 * a) % mod;
        b >>= 1;
    }
    return result;
}

int powmod(int a, int b, int mod) {
    int result = 1;
    a %= mod;
    while (b) {
        if (b & 1)
            result = mulmod(result, a, mod);
        a = mulmod(a, a, mod);
        b >>= 1;
    }
    return result;
}

bool is_prime(int n) {
    if (n < 2) return false;
    for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n % p == 0) return n == p;
    }
    int d = n - 1, s = 0;
    while ((d & 1) == 0) d >>= 1, s++;

    for (int a : {2, 3, 5, 7, 11}) {
        if (a >= n) continue;
        int x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; ++r) {
            x = mulmod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

int next_prime(int n) {
    int x = n + 1;
    while (!is_prime(x)) x++;
    return x;
}

void solve() {
    int t; cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << next_prime(n) << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
