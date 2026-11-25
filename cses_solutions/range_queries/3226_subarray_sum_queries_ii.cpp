#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct Node {
    int sum, pre, suff, ans;
    Node(int val = 0) {
        sum = val;
        pre = suff = ans = max(val, 0LL); // allow empty subarray
    }
};

Node combine(const Node& L, const Node& R) {
    Node res;
    res.sum = L.sum + R.sum;
    res.pre = max(L.pre, L.sum + R.pre);
    res.suff = max(R.suff, R.sum + L.suff);
    res.ans = max({L.ans, R.ans, L.suff + R.pre});
    return res;
}

const int MAXN = 2e5 + 5;
Node seg[4 * MAXN];
int arr[MAXN];

void build(int id, int l, int r) {
    if (l == r) {
        seg[id] = Node(arr[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    seg[id] = combine(seg[id * 2], seg[id * 2 + 1]);
}

Node query(int id, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return Node(0); // neutral for empty
    if (ql <= l && r <= qr) return seg[id];
    int mid = (l + r) / 2;
    Node left = query(id * 2, l, mid, ql, qr);
    Node right = query(id * 2 + 1, mid + 1, r, ql, qr);
    return combine(left, right);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> arr[i];

    build(1, 1, n);

    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << query(1, 1, n, a, b).ans << endl;
    }
}
