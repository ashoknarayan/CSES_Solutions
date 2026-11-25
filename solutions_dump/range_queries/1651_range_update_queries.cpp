#include <bits/stdc++.h>
 
#define range(it, a, b) for (ll it = a; it < b; it++)
#define all(x) begin(x), end(x)
#define ll long long
#define ull unsigned long long
#define INF64 ((ll) 1 << 60)
#define INF32 (1 << 30)
#define uset unordered_set
#define umap unordered_map 
#define pqueue priority_queue
 
using namespace std;
 
void setio (string name) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (name.size()) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }   
}
 
struct BIT {
    vector<ll> bit;
 
    BIT (ll size) {
        bit.resize(size);
    }
 
    void update (ll i, ll delta) {
        for ( ; i < bit.size(); i |= i + 1) {
            bit[i] += delta;
        }
    }
 
    void update (ll l, ll r, ll delta) {
        update(l, delta);
        update(r + 1, -delta);
    }
 
    ll get (ll i) {
        ll sum = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1)
            sum += bit[i];
        return sum;
    }
};
 
ll n, q;
vector<ll> arr;
 
void solve() {
    cin >> n >> q;
    arr.resize(n);
    range(i, 0, n) cin >> arr[i];
    BIT ft (arr.size());
 
    ll t, l, r, u;
    while (q--) {
        cin >> t;
        if (t == 1) {
            cin >> l >> r >> u;
            l--; r--;
            ft.update(l, r, u);
        }
        else {
            cin >> l;
            l--;
            cout << arr[l] + ft.get(l) << '\n';
        }
    }
}
 
int main () {
    setio("");
    ll t = 1; 
    // cin >> t;
    while (t--) solve();
}
 
/*

FENWICK TREE
 
 
*/
