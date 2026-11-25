#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

const int INF = 1e18;

struct SegmentTree {
    int n;
    vector<int> tree;

    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, 0);
    }

    void update(int idx, int val, int node = 1, int l = 0, int r = -1) {
        if (r == -1) r = n - 1;
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid)
            update(idx, val, 2 * node, l, mid);
        else
            update(idx, val, 2 * node + 1, mid + 1, r);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    int query(int ql, int qr, int node = 1, int l = 0, int r = -1) {
        if (r == -1) r = n - 1;
        if (qr < l || ql > r) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return max(query(ql, qr, 2 * node, l, mid),
                   query(ql, qr, 2 * node + 1, mid + 1, r));
    }
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> h(n);
    for (int &x : h) cin >> x;

    // Step 1: Compute L[i] and R[i] using monotonic stack
    vector<int> L(n, -1), R(n, n);
    stack<int> st;

    // Left greater
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && h[st.top()] <= h[i])
            st.pop();
        if (!st.empty()) L[i] = st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();

    // Right greater
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && h[st.top()] <= h[i])
            st.pop();
        if (!st.empty()) R[i] = st.top();
        st.push(i);
    }

    // Step 2: Process in increasing order of height
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return h[a] < h[b];
    });

    vector<int> dp(n, 1);
    SegmentTree seg(n);

    for (int i = 0; i < n;) {
        int j = i;
        // Process all with same height together
        while (j < n && h[idx[j]] == h[idx[i]]) {
            int pos = idx[j];
            int l = L[pos] + 1;
            int r = R[pos] - 1;
            if (l <= r)
                dp[pos] = 1 + seg.query(l, r);
            ++j;
        }
        // Then update the segment tree after calculating all dp
        for (int k = i; k < j; ++k)
            seg.update(idx[k], dp[idx[k]]);
        i = j;
    }

    cout << *max_element(dp.begin(), dp.end()) << endl;
}
