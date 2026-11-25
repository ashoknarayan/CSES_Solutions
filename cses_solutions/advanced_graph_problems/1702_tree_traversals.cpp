#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

int n;
vector<int> preorder, inorder;
unordered_map<int, int> in_pos;
vector<int> post;

void dfs(int preL, int preR, int inL, int inR) {
    while (preL <= preR && inL <= inR) {
        int root = preorder[preL];
        int idx = in_pos[root];
        int leftSize = idx - inL;

        // Recurse left
        if (leftSize > 0)
            dfs(preL + 1, preL + leftSize, inL, idx - 1);
        // Recurse right
        if (preL + leftSize + 1 <= preR)
            dfs(preL + leftSize + 1, preR, idx + 1, inR);

        post.push_back(root);
        return;
    }
}

void solve() {
    cin >> n;
    preorder.resize(n);
    inorder.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> preorder[i];
    for (int i = 0; i < n; ++i) {
        cin >> inorder[i];
        in_pos[inorder[i]] = i;
    }

    dfs(0, n - 1, 0, n - 1);

    for (int x : post)
        cout << x << " ";
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}
