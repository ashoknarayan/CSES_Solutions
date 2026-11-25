#include <bits/stdc++.h>
using namespace std;
#define int long long

int countDistinctSubsetXors(vector<int>& a) {
    vector<int> basis(60, 0);
    int k = 0;
    for (int x : a) {
        for (int i = 59; i >= 0; i--) {
            if ((x >> i) & 1) {
                if (!basis[i]) {
                    basis[i] = x;
                    k++;
                    break;
                }
                x ^= basis[i];
            }
        }
    }
    return 1LL << k; // 2^k subsets
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    cout << countDistinctSubsetXors(a) << "\n";
}
