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

ll n, q;
vector<ll> arr, suf, psum;

struct SegTree {
    struct Node {
        Node* left;
        Node* right;
        ll l, r;
        ll maxi;

        ll get_l() { return (l+r)/2; }
        ll get_r() { return get_l()+1; }
    };

    Node* root;

    SegTree() {
        root = new Node;
        root->l = 0;
        root->r = arr.size() - 1;
        build(root);
    }

    void build(Node* node) {
        if (node->l == node->r) {
            node->maxi = node->l;
            return;
        }

        node->left = new Node;
        node->left->l = node->l;
        node->left->r = node->get_l();
        build(node->left);

        node->right = new Node;
        node->right->l = node->get_r();
        node->right->r = node->r;
        build(node->right);

        node->maxi = (arr[node->left->maxi] > arr[node->right->maxi] ? node->left->maxi : node->right->maxi);
    }

    ll query(Node* node, ll l, ll r) {
        if (node->l == l && node->r == r)
            return node->maxi;

        ll ans = -1;
        if (l <= node->get_l())
            ans = query(node->left, l, min(r, node->get_l()));
        if (r >= node->get_r()) {
            ll aux = query(node->right, max(l, node->get_r()), r);
            if (ans == -1 || arr[aux] > arr[ans])
                ans = aux;
        }
        return ans;
    }

    ll query(ll l, ll r) {
        return query(root, l, r);
    }
};

void solve() {
    cin >> n >> q;
    arr.resize(n);
    suf.resize(n);
    psum.resize(n);

    range(i,0,n)
        cin >> arr[i];

    stack<ll> sk;
    for (ll i = n-1; i >= 0; i--) {
        while (!sk.empty() && arr[sk.top()] <= arr[i])
            sk.pop();
        if (sk.empty())
            suf[i] = arr[i]*(n-i);
        else
            suf[i] = suf[sk.top()]+(arr[i]*(sk.top()-i));
        sk.push(i);
    }

    SegTree st;

    range(i, 0, n)
        psum[i] = arr[i] + (i ? psum[i-1] : 0);

    ll a, b;
    while (q--) {
        cin >> a >> b;
        a--; b--;
        ll m = st.query(a, b);
        ll sum = suf[a] - suf[m] + (arr[m]*(b-m+1));
        cout << sum - (psum[b] - (a ? psum[a-1] : 0)) << '\n';
    }
}

int main () {
    setio("");
    ll t = 1;
    // cin >> t;
    while (t--) solve();
}




/*!
This was a big problem. Have to work on this further
*/
