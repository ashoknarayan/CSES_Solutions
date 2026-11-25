#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int MAX_X = 1e5;

struct Line {
    int a, b; // y = ax + b
    Line(int _a = 0, int _b = -1e18) : a(_a), b(_b) {}
    int eval(int x) const {
        return a * x + b;
    }
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

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    LiChaoTree cht(0, MAX_X + 1); // queries are in range [0, 1e5]

    while (n--) {
        int type;
        cin >> type;
        if (type == 1) {
            int a, b;
            cin >> a >> b;
            cht.addLine(Line(a, b));
        } else {
            int x;
            cin >> x;
            cout << cht.query(x) << endl;
        }
    }
}
