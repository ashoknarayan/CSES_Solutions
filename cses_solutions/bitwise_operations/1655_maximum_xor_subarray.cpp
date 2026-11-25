#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXB = 31; // since max value of x_i is up to 10^9 (~30 bits)

struct TrieNode {
    TrieNode* child[2] = {nullptr, nullptr};
};

void insert(TrieNode* root, int num) {
    TrieNode* node = root;
    for (int i = MAXB; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (!node->child[bit])
            node->child[bit] = new TrieNode();
        node = node->child[bit];
    }
}

int query(TrieNode* root, int num) {
    TrieNode* node = root;
    int res = 0;
    for (int i = MAXB; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (node->child[1 - bit]) {
            res |= (1LL << i);
            node = node->child[1 - bit];
        } else {
            node = node->child[bit];
        }
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    TrieNode* root = new TrieNode();
    insert(root, 0); // Important: prefix_xor of empty subarray

    int max_xor = 0, pref = 0;
    for (int x : a) {
        pref ^= x;
        max_xor = max(max_xor, query(root, pref));
        insert(root, pref);
    }

    cout << max_xor << '\n';
}
