#include<bits/stdc++.h>
using namespace std;
#define int long long

const int MOD = 1e9 + 7;

struct FenwickTree {
    vector<int> bit;
    int n;
    FenwickTree(int size) {
        n = size;
        bit.assign(n+1, 0);
    }
    void update(int idx, int val) {
        while(idx <= n) {
            bit[idx] = (bit[idx] + val) % MOD;
            idx += idx & -idx;
        }
    }
    int query(int idx) {
        int res = 0;
        while(idx > 0) {
            res = (res + bit[idx]) % MOD;
            idx -= idx & -idx;
        }
        return res;
    }
};

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(n), comp;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        comp.push_back(a[i]);
    }

    // Coordinate compression
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());

    FenwickTree bit(comp.size());
    int total = 0;

    for(int i = 0; i < n; ++i) {
        int idx = lower_bound(comp.begin(), comp.end(), a[i]) - comp.begin() + 1;
        int count = bit.query(idx - 1);  // all subsequences ending in values < a[i]
        bit.update(idx, (count + 1) % MOD);  // +1 for subsequence of just a[i]
    }

    cout << bit.query(comp.size()) << '\n';
}
