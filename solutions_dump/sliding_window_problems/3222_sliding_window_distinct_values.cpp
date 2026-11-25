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
 
    map<int, int> freq;
    int distinct = 0;
 
    for (int i = 0; i < k; ++i) {
        if (++freq[a[i]] == 1) ++distinct;
    }
 
    cout << distinct << ' ';
 
    for (int i = k; i < n; ++i) {
        // Remove a[i - k]
        if (--freq[a[i - k]] == 0)
            --distinct;
        // Add a[i]
        if (++freq[a[i]] == 1)
            ++distinct;
        cout << distinct << ' ';
    }
 
    cout << endl;
}
