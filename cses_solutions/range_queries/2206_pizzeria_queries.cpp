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

struct SegTree {
    struct Node {
        ll l, r, mini, lazy;
        ptr(Node) left, right;

        ll get_l() { return (l + r) / 2; }
        ll get_r() { return get_l() + 1; }
    };

    ptr(Node) root;

    SegTree () { }

    void init (ll sz) {
        root = ptr(Node) (new Node);
        root->l = 0; root->r = sz - 1;
        build(root);
    }

    void build(ptr(Node) node) {
        if (node->l == node->r)
            return;

        node->left = ptr(Node) (new Node);
        node->left->l = node->l;
        node->left->r = node->get_l();
        build(node->left);

        node->right = ptr(Node) (new Node);
        node->right->l = node->get_r();
        node->right->r = node->r;
        build(node->right);
    }

    void update(ll i, ptr(Node) node, ll delta) {
        if (node->l == node->r) {
            node->mini = delta;
            return;
        }

        if (i <= node->get_l())
            update(i, node->left, delta);
        else
            update(i, node->right, delta);

        node->mini = min(node->right->mini, node->left->mini);
    }

    void update(ll i, ll delta) { update(i, root, delta); }

    ll query(ll l, ll r, ptr(Node) node) {
        if (node->l == l && node->r == r)
            return node->mini;

        ll ans = INF64;
        if (l <= node->get_l())
            ans = query(l, min(r, node->get_l()), node->left);
        if (r >= node->get_r())
            ans = min(ans, query(max(l, node->get_r()), r, node->right));
        return ans;
    }

    ll query(ll l, ll r) { return query(l, r, root); }
};

ll n, q;
vector<ll> arr;
SegTree down, up;

void update(ll i) {
    down.update(i, arr[i] - i);
    up.update(i, arr[i] + i);
}

void solve() {
    cin >> n >> q;
    arr.resize(n);

    down.init(n); up.init(n);
    range(i, 0, n) {
        cin >> arr[i];
        update(i);
    }

    range(i, 0, q) {
        ll t; cin >> t;
        if (t == 1) {
            ll it, nt; cin >> it >> nt;
            arr[--it] = nt;
            update(it);
            continue;
        }
        ll it; cin >> it; it--;
        cout << min(down.query(0, it) + it, up.query(it, n - 1) - it) << '\n';
    }
}

int main () {
    setio("");
    ll t = 1;
    // cin >> t;
    while (t--) solve();
}

/*!
Range Maximum Queries Segment Trees
*/
