#include <bits/stdc++.h>

#define range(it, a, b) for (ll it = a; it < b; it++)
#define all(x) begin(x), end(x)
#define ll long long
#define ull unsigned long long
#define INF64 ((ll) 1 << 60)
#define INF32 (1 << 30)
#define mset multiset
#define uset unordered_set
#define umap unordered_map
#define pqueue priority_queue
#define ptr(A) shared_ptr<A>

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

    BIT () { bit.resize((ll) 6e5); }

    ll get(ll i) {
        ll sum = 0;
        for ( ; i >= 0; i = (i & (i + 1)) - 1)
            sum += bit[i];
        return sum;
    }

    void update(ll i, ll delta) {
        for ( ; i < bit.size(); i |= (i + 1))
            bit[i] += delta;
    }

    ll get (ll l, ll r) { return get(r) - get(l - 1); }
};

BIT ft;
ll n, q;
vector<ll> arr;
vector<pair<ll, ll>> comp;

ll cast(ll x) {
    auto lb = lower_bound(all(comp), pair<ll, ll> (x, 0));
    return (*lb).second;
}

struct Query {
    char t;
    ll a, b;

    void execute () {
        if (t == '!') {
            ft.update(cast(arr[a]), -1);
            arr[a] = b;
            ft.update(cast(arr[a]), 1);
            return;
        }

        cout << ft.get(cast(a), cast(b)) << '\n';
    }
};

vector<Query> qr;

void solve() {
    cin >> n >> q;
    arr.resize(n);

    range(i, 0, n) {
        cin >> arr[i];
        comp.push_back({arr[i], 0});
    }

    char t;
    ll a, b;
    range(i, 0, q) {
        cin >> t >> a >> b;
        if (t == '!') {
            a--;
            comp.push_back({b, 0});
        }
        else {
            comp.push_back({a, 0});
            comp.push_back({b, 0});
        }

        qr.push_back({t, a, b});
    }

    sort(all(comp));

    ll cnt = 0;
    range(i, 0, comp.size()) {
        if (i && comp[i - 1].first != comp[i].first)
            cnt++;

        comp[i].second = cnt;
    }

    for (ll i : arr)
        ft.update(cast(i), 1);

    for (Query& it : qr)
        it.execute();
}

int main () {
    setio("");
    ll t = 1;
    // cin >> t;
    while (t--) solve();
}


/*!
Can use both BIT or Segment Tree
To save memory we use a method called coordinate compression
*/
