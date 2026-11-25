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
        ptr(Node) left, right;
        ll l, r, max, pre, suf, sum;

        ll get_l () { return (l + r) / 2; }
        ll get_r () { return get_l() + 1; }
    };

    vector<ll>& arr;
    ptr(Node) root;

    SegTree(vector<ll>& a) : arr(a) {
        root = ptr(Node) (new Node);
        root->l = 0;
        root->r = a.size() - 1;
        build(root);
    }

    void build (ptr(Node) node) {
        if (node->l == node->r) {
            node->max = arr[node->l];
            node->pre = node->max;
            node->suf = node->max;
            node->sum = node->max;
            return;
        }

        node->left = ptr(Node) (new Node);
        node->left->l = node->l;
        node->left->r = node->get_l();
        build(node->left);

        node->right = ptr(Node) (new Node);
        node->right->l = node->get_r();
        node->right->r = node->r;
        build(node->right);

        node->max = max({node->left->max, node->right->max, node->left->suf + node->right->pre});
        node->sum = node->left->sum + node->right->sum;
        node->pre = max(node->left->pre, node->left->sum + node->right->pre);
        node->suf = max(node->right->suf, node->right->sum + node->left->suf);
    }

    void update(ll i, ll d, ptr(Node) node) {
        if (node->l == node->r) {
            node->max = d;
            node->pre = node->max;
            node->suf = node->max;
            node->sum = node->max;
            return;
        }

        if (i <= node->get_l())
            update(i, d, node->left);
        if (node->get_r() <= i)
            update(i, d, node->right);

        node->max = max({node->left->max, node->right->max, node->left->suf + node->right->pre});
        node->sum = node->left->sum + node->right->sum;
        node->pre = max(node->left->pre, node->left->sum + node->right->pre);
        node->suf = max(node->right->suf, node->right->sum + node->left->suf);
    }

    ll update(ll i, ll d) {
        update(i, d, root);
        return root->max;
    }
};

ll n, q;

void solve() {
    cin >> n >> q;

    vector<ll> arr(n);
    range(i, 0, n)
        cin >> arr[i];

    SegTree st (arr);
    while (q--) {
        ll k, x;
        cin >> k >> x;
        k--;
        cout << max(0ll, st.update(k, x)) << '\n';
    }
}

int main () {
    setio("");
    ll t = 1;
    // cin >> t;
    while (t--) solve();
}


/*!
Observations
There are three possible ways the answer could be found:

The answer is entirely in the left child, this being the answer of the left child.
The answer is entirely in the right child, this being the answer of the right child.
The answer is partially in both the left and right children. This means a suffix of the left child and a prefix of the right child.
This means that we need each node of the tree to store the answer for itself, as well as the maximum suffix and prefix in it.

Now it can be solved with segment trees !
*/
