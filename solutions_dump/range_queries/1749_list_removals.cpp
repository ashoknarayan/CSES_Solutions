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
    }};
 
ll n, q;
vector<ll> arr;


ll bs (ll x, BIT& ft) {
    ll l = 0, r = n - 1, m;
    while (l < r) {
        m = (l + r) / 2;
        if (ft.get(m) >= x)
            r = m;
        else 
            l = m + 1;
    }
    return l;
} 


void solve() {
    cin >> n;
    arr.resize(n);
 
    BIT ft (n);
    range(i, 0, n) {
        cin >> arr[i];
        ft.update(i, 1);
    } 
    
    ll x;
    range(i, 0, n) {
        cin >> x;
        ll it = bs(x, ft);
        cout << arr[it] << ' ';
        ft.update(it, -1);
    }
}
 
int main () 
{
    ll t = 1; 
    // cin >> t;
    while (t--) solve();
}

/*
This is fr FENWICK TREE.

*/
