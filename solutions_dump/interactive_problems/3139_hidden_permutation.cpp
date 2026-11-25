#include <bits/stdc++.h>
using namespace std;

int n;

// Ask if a_i < a_j (1-based indices)
bool ask(int i, int j) {
    cout << "? " << i << " " << j << endl;
    cout.flush();
    string response;
    cin >> response;
    return response == "YES";
}

void merge_sort(vector<int>& v, int l, int r) {
    if (r - l <= 1) return;
    int m = (l + r) / 2;
    merge_sort(v, l, m);
    merge_sort(v, m, r);

    vector<int> temp;
    int i = l, j = m;
    while (i < m && j < r) {
        if (ask(v[i], v[j])) temp.push_back(v[i++]);
        else temp.push_back(v[j++]);
    }
    while (i < m) temp.push_back(v[i++]);
    while (j < r) temp.push_back(v[j++]);

    for (int k = l; k < r; ++k)
        v[k] = temp[k - l];
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 1);

    merge_sort(idx, 0, n);

    vector<int> ans(n);
    for (int i = 0; i < n; ++i)
        ans[idx[i] - 1] = i + 1;

    cout << "! ";
    for (int x : ans) cout << x << " ";
    cout << endl;
    cout.flush();

    return 0;
}
