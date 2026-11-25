#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i] = {x, i};
    }

    // Sort by value, ties broken by original index
    sort(a.begin(), a.end());

    int rounds = 0;
    for (int sorted_index = 0; sorted_index < n; sorted_index++) {
        int original_index = a[sorted_index].second;
        rounds = max(rounds, original_index - sorted_index);
    }

    cout << rounds << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
