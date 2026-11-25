#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int long long
#define endl '\n'
#define pii pair<int,int>
#define fast_io ios::sync_with_stdio(0); cin.tie(0)

typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

signed main() {
    fast_io;
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    ordered_set os;
    vector<int> ans;
    int inv = 0;

    for (int i = 0; i < k; ++i) {
        inv += os.size() - os.order_of_key({a[i], i});
        os.insert({a[i], i});
    }

    ans.push_back(inv);

    for (int i = k; i < n; ++i) {
        // Remove a[i - k]
        inv -= os.order_of_key({a[i - k], i - k});
        os.erase({a[i - k], i - k});

        // Add a[i]
        inv += os.size() - os.order_of_key({a[i], i});
        os.insert({a[i], i});

        ans.push_back(inv);
    }

    for (int x : ans) cout << x << ' ';
    cout << endl;
    return 0;
}
