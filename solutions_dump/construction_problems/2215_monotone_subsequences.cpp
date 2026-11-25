#include <bits/stdc++.h>
using namespace std;

void solve(int n, int k) {
    if (k * k < n) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    vector<int> res;
    int val = 1;
    for (int i = 0; i < k; ++i) {
        int block_size = (n - val + 1 + k - i - 1) / (k - i);  // ceil division
        vector<int> block;
        for (int j = 0; j < block_size; ++j)
            block.push_back(val + j);
        reverse(block.begin(), block.end());
        for (int x : block) res.push_back(x);
        val += block_size;
    }

    for (int x : res) cout << x << " ";
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        solve(n, k);
    }
}
