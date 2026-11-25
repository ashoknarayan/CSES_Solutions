#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

void solve() {
    int n;
    cin >> n;
    vector<int> code(n - 2);
    vector<int> degree(n + 1, 1);

    for (int& x : code) {
        cin >> x;
        degree[x]++;
    }

    // Min-heap to find smallest leaf
    set<int> leaves;
    for (int i = 1; i <= n; ++i)
        if (degree[i] == 1)
            leaves.insert(i);

    for (int x : code) {
        int leaf = *leaves.begin();
        leaves.erase(leaves.begin());

        cout << leaf << " " << x << endl;

        if (--degree[x] == 1)
            leaves.insert(x);
    }

    // Last two remaining nodes
    auto it = leaves.begin();
    int u = *it;
    int v = *(++it);
    cout << u << " " << v << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
