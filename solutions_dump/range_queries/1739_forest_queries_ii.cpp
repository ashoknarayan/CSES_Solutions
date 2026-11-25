#include <bits/stdc++.h>

#define range(it, a, b) for (ll it = a; it < b; it++)
#define all(x) begin(x), end(x)
#define ll long long
#define ull unsigned long long
#define INF64 ((ll) 1 << 62)
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

struct BIT2 {
    struct BIT {
        ll bit[1000];

        void update(ll i, ll delta) {
            for ( ; i < 1000; i |= i + 1)
                bit[i] += delta;
        }

        ll query(ll i) {
            ll sum = 0;
            for ( ; i >= 0; i = (i & (i + 1)) - 1)
                sum += bit[i];
            return sum;
        }

        ll query(ll l, ll r) {
            return query(r) - (l ? query(l - 1) : 0);
        }
    };

    BIT bit[1000];

    void update(ll i, ll j, ll delta) {
        for ( ; i < 1000; i |= i + 1)
            bit[i].update(j, delta);
    }

    ll query(ll y, ll i, ll j) {
        ll sum = 0;
        for ( ; y >= 0; y = (y & (y + 1)) - 1)
            sum += bit[y].query(i, j);
        return sum;
    }

    ll query(ll l, ll r, ll i, ll j) {
        return query(r, i, j) - (l ? query(l - 1, i, j) : 0);
    }
};

ll n, q;
bool mat[1000][1000];
BIT2 ft;

void solve() {
    cin >> n >> q;

    char x;
    range(i, 0, n) {
        range(j, 0, n) {
            cin >> x;
            mat[i][j] = (x == '*');
            if (mat[i][j])
                ft.update(i, j, 1);
        }
    }

    ll t;
    while (q--) {
        cin >> t;
        if (t == 1) {
            ll i, j;
            cin >> i >> j;
            i--; j--;
            ft.update(i, j, (mat[i][j] ? -1 : 1));
            mat[i][j] = !mat[i][j];
            continue;
        }

        ll l, i, r, j;
        cin >> l >> i >> r >> j;
        l--; i--; r--; j--;
        cout << ft.query(l, r, i, j) << '\n';
    }
}

int main () {
    setio("");
    ll t = 1;
    // cin >> t;
    while (t--) solve();
}




/*!
I have solved Forest Queries 1
Now we have to extend to this solution by using BIT in 2D
Dont know what they are doing. But will learn soon
*/
