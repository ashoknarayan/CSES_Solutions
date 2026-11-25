#include <bits/stdc++.h>
using namespace std;

struct ImplicitTreap {
    struct Node {
        char val;
        int prior, sz;
        bool rev;
        Node *l, *r;
        Node(char v, int p) : val(v), prior(p), sz(1), rev(0), l(nullptr), r(nullptr) {}
    };

    using pNode = Node*;
    mt19937 rng{chrono::steady_clock::now().time_since_epoch().count()};
    pNode root = nullptr;

    int sz(pNode t) { return t ? t->sz : 0; }

    void pull(pNode t) {
        if (t) t->sz = 1 + sz(t->l) + sz(t->r);
    }

    void push(pNode t) {
        if (!t || !t->rev) return;
        swap(t->l, t->r);
        if (t->l) t->l->rev ^= 1;
        if (t->r) t->r->rev ^= 1;
        t->rev = 0;
    }

    void split(pNode t, pNode &l, pNode &r, int k) {
        if (!t) {
            l = r = nullptr;
            return;
        }
        push(t);
        if (sz(t->l) >= k) {
            split(t->l, l, t->l, k);
            r = t;
        } else {
            split(t->r, t->r, r, k - sz(t->l) - 1);
            l = t;
        }
        pull(t);
    }

    pNode merge(pNode l, pNode r) {
        if (!l || !r) return l ? l : r;
        if (l->prior > r->prior) {
            push(l);
            l->r = merge(l->r, r);
            pull(l);
            return l;
        } else {
            push(r);
            r->l = merge(l, r->l);
            pull(r);
            return r;
        }
    }

    void build(const string &s) {
        for (char c : s)
            root = merge(root, new Node(c, rng()));
    }

    void reverse(int l, int r) {
        pNode t1, t2, t3;
        split(root, t1, t2, l - 1);
        split(t2, t2, t3, r - l + 1);
        if (t2) t2->rev ^= 1;
        root = merge(t1, merge(t2, t3));
    }

    void dfs(pNode t) {
        if (!t) return;
        push(t);
        dfs(t->l);
        cout << t->val;
        dfs(t->r);
    }

    void print() {
        dfs(root);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    ImplicitTreap treap;
    treap.build(s);

    while (m--) {
        int l, r;
        cin >> l >> r;
        treap.reverse(l, r);
    }

    treap.print();
}
