#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int MAX_X = 1e5;

struct Line {
    int a, b;
    Line(int _a = 0, int _b = -1e18) : a(_a), b(_b) {}
    int eval(int x) const { return a * x + b; }
};

struct Node {
    Line line;
    Node *left, *right;
    Node() : line(), left(nullptr), right(nullptr) {}
};

struct LiChaoTree {
    Node* root;
    int low, high;

    LiChaoTree(int _low, int _high) : low(_low), high(_high) {
        root = new Node();
    }

    void addLine(Line newLine) {
        addLine(root, low, high, newLine);
    }

    void addLine(Node* node, int l, int r, Line newLine) {
        int mid = (l + r) / 2;
        bool leftBetter = newLine.eval(l) > node->line.eval(l);
        bool midBetter  = newLine.eval(mid) > node->line.eval(mid);

        if (midBetter) swap(node->line, newLine);
        if (r - l == 1) return;

        if (leftBetter != midBetter) {
            if (!node->left) node->left = new Node();
            addLine(node->left, l, mid, newLine);
        } else {
            if (!node->right) node->right = new Node();
            addLine(node->right, mid, r, newLine);
        }
    }

    int query(int x) {
        return query(root, low, high, x);
    }

    int query(Node* node, int l, int r, int x) {
        if (!node) return -1e18;
        int res = node->line.eval(x);
        if (r - l == 1) return res;
        int mid = (l + r) / 2;
        if (x < mid) return max(res, query(node->left, l, mid, x));
        else return max(res, query(node->right, mid, r, x));
    }
};

// Segment Tree of Li Chao Trees
const int MAXN = 1 << 18;
LiChaoTree* seg[2 * MAXN];

void insert(int node, int l, int r, int ql, int qr, Line ln) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) {
        if (!seg[node]) seg[node] = new LiChaoTree(0, MAX_X + 1);
        seg[node]->addLine(ln);
        return;
    }
    int mid = (l + r) / 2;
    insert(2*node, l, mid, ql, qr, ln);
    insert(2*node+1, mid+1, r, ql, qr, ln);
}

int query(int node, int l, int r, int x) {
    if (x < l || x > r) return -1e18;
    int res = -1e18;
    if (seg[node]) res = seg[node]->query(x);
    if (l == r) return res;
    int mid = (l + r) / 2;
    if (x <= mid) res = max(res, query(2*node, l, mid, x));
    else res = max(res, query(2*node+1, mid+1, r, x));
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    while (n--) {
        int type;
        cin >> type;
        if (type == 1) {
            int a, b, l, r;
            cin >> a >> b >> l >> r;
            insert(1, 0, MAX_X, l, r, Line(a, b));
        } else {
            int x;
            cin >> x;
            int res = query(1, 0, MAX_X, x);
            if (res == -1e18) cout << "NO" << endl;
            else cout << res << endl;
        }
    }
}
