#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXB = 60; // Since 10^9 fits in 30 bits, but for safety we use 60

int maxXorSubset(vector<int>& a) {
    vector<int> basis(MAXB, 0); // basis[i] keeps mask with i-th bit set

    for (int x : a) {
        for (int i = MAXB - 1; i >= 0; i--) {
            if (!(x & (1LL << i))) continue;
            if (!basis[i]) {
                basis[i] = x;
                break;
            }
            x ^= basis[i];
        }
    }

    int res = 0;
    for (int i = MAXB - 1; i >= 0; i--) {
        res = max(res, res ^ basis[i]);
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    cout << maxXorSubset(a) << '\n';
}
