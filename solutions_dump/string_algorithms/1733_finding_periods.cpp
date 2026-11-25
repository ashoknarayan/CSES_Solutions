#include <bits/stdc++.h>
using namespace std;

vector<int> z(string s) {
    int n = s.size();
    vector<int> zz(n, 0);
    int x = 0, y = 0;

    for (int i = 1; i < n; ++i) {
        if (i <= y) {
            zz[i] = min(zz[i - x], y - i + 1);
        }
        while (i + zz[i] < n && s[zz[i]] == s[i + zz[i]]) {
            zz[i]++;
        }
        if (i + zz[i] - 1 > y) {
            x = i;
            y = i + zz[i] - 1;
        }
    }

    vector<int> ans;
    for (int i = 1; i < n; ++i) {
        if (zz[i] + i == n) ans.push_back(i);
    }
    ans.push_back(n);
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string s; cin >> s;
    for (int i : z(s)) cout << i << " ";
    cout << endl;
    return 0;
}

// This is called as Z-Alg.
