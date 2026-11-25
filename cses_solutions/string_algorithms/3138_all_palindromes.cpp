#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 2e5 + 5;
const int ALPHA = 26;

struct Node {
    int len, link;
    int next[ALPHA];
    Node() {
        len = 0;
        link = 0;
        memset(next, -1, sizeof(next));
    }
};

Node tree[MAXN];
int suff, sz;
string s;
int ans[MAXN];

void init() {
    tree[0].len = 0;
    tree[0].link = 1;
    tree[1].len = -1;
    tree[1].link = 1;
    sz = 2;
    suff = 0;
}

void add_char(int pos) {
    int cur = suff;
    int c = s[pos] - 'a';

    while (true) {
        int curlen = tree[cur].len;
        if (pos - curlen - 1 >= 0 && s[pos - curlen - 1] == s[pos])
            break;
        cur = tree[cur].link;
    }

    if (tree[cur].next[c] != -1) {
        suff = tree[cur].next[c];
        return;
    }

    suff = sz++;
    tree[cur].next[c] = suff;
    tree[suff].len = tree[cur].len + 2;

    if (tree[suff].len == 1) {
        tree[suff].link = 0;
    } else {
        int link = tree[cur].link;
        while (true) {
            int len = tree[link].len;
            if (pos - len - 1 >= 0 && s[pos - len - 1] == s[pos])
                break;
            link = tree[link].link;
        }
        tree[suff].link = tree[link].next[c];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    int n = s.size();

    init();
    for (int i = 0; i < n; i++) {
        add_char(i);
        ans[i] = tree[suff].len;
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << '\n';

    return 0;
}
