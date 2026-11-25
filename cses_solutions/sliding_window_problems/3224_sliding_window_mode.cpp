#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &x : a) cin >> x;

    unordered_map<int, int> freq;
    map<int, set<int>> freq_buckets;

    auto insert = [&](int x) {
        int f = freq[x]++;
        if (f > 0) {
            freq_buckets[f].erase(x);
            if (freq_buckets[f].empty()) freq_buckets.erase(f);
        }
        freq_buckets[f + 1].insert(x);
    };

    auto remove = [&](int x) {
        int f = freq[x]--;
        freq_buckets[f].erase(x);
        if (freq_buckets[f].empty()) freq_buckets.erase(f);
        if (freq[x] > 0)
            freq_buckets[f - 1].insert(x);
        else
            freq.erase(x);
    };

    for (int i = 0; i < k; ++i)
        insert(a[i]);

    cout << *freq_buckets.rbegin()->second.begin() << ' ';

    for (int i = k; i < n; ++i) {
        insert(a[i]);
        remove(a[i - k]);
        cout << *freq_buckets.rbegin()->second.begin() << ' ';
    }

    cout << endl;
}
