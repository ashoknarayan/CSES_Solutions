#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n; vector<int> a(n);
    for (int &x : a) cin >> x;
    vector<int> ans = a;
    int m = 0; while ((1 << m) < n) m++;
    for (int b = 0; b < m; b++) 
        for (int mask = 0; mask < n; mask++) 
            if (mask & (1 << b)) 
                ans[mask] ^= ans[mask ^ (1 << b)];
    for (int x : ans) cout << x << ' ';
    cout << '\n';
    return 0;
}
// Something called Fast Zeta Trasform
