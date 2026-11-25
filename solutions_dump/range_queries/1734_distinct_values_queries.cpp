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

const ll SQR = 600;

struct TQuery {
    ll l, r, i;
    ll ans;
};
struct TVal {
    ll x, i;
};

ll n, q, cnt = 1;
TVal arr [(ll)2e5];
TQuery qr [(ll)2e5];
ll freq [(ll)2e5];

void move(ll& l, ll& r, ll& a, ll& b) {
    while (a < l) {
        l--;
        if (++freq[arr[l].x] == 1)
            cnt++;
    }
    while (r < b) {
        r++;
        if (++freq[arr[r].x] == 1)
            cnt++;
    }
    while (l < a) {
        if (--freq[arr[l].x] == 0)
            cnt--;
        l++;
    }
    while (b < r) {
        if (--freq[arr[r].x] == 0)
            cnt--;
        r--;
    }
}

void compress() {
    sort(arr, arr+n, [](const TVal& a, const TVal& b) {
        return a.x < b.x;
    });
    ll last = arr[0].x, aux;
    arr[0].x = 0;
    range(i, 1, n) {
        aux = arr[i].x;
        arr[i].x = arr[i-1].x + (last != arr[i].x);
        last = aux;
    }
    sort(arr, arr+n, [](const TVal& a, const TVal& b) {
        return a.i < b.i;
    });
}

void solve() {
    cin >> n >> q;

    range(i, 0, n) {
        cin >> arr[i].x;
        arr[i].i = i;
    }
    compress();

    range(i, 0, q) {
        cin >> qr[i].l >> qr[i].r;
        qr[i].l--; qr[i].r--;
        qr[i].i = i;
    }
    sort(qr, qr+q, [](const TQuery& a, const TQuery& b) {
        if (a.l/SQR == b.l/SQR)
            return a.r < b.r;
        return a.l/SQR < b.l/SQR;
    });

    freq[arr[0].x] = 1;
    ll l = 0, r = 0;
    range(i, 0, q) {
        move(l, r, qr[i].l, qr[i].r);
        qr[i].ans = cnt;
    }
    sort(qr, qr+q, [](const TQuery& a, const TQuery& b) {
        return a.i < b.i;
    });

    range(i, 0, q)
        cout << qr[i].ans << '\n';
}

int main () {
    setio("");
    ll t = 1;
    // cin >> t;
    while (t--) solve();
}



/*!
Mo's Alg
This is the prerequisite for the upcoming trees question of distinct colours
*/
