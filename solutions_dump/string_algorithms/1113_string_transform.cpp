// inverse Burrows-Wheeler Transform (BWT)
#include <bits/stdc++.h>
using namespace std;

void solve() {
    string L;
    cin >> L;
    int n = L.size();
    string F = L;
    sort(F.begin(), F.end());
    map<char, queue<int>> pos_map;
    for (int i = 0; i < n; ++i) {
        pos_map[F[i]].push(i);
    }
    vector<int> LF(n);
    for (int i = 0; i < n; ++i) {
        LF[i] = pos_map[L[i]].front();
        pos_map[L[i]].pop();
    }
    int idx = -1;
    for (int i = 0; i < n; ++i) {
        if (L[i] == '#') {
            idx = i;
            break;
        }
    }
    string res;
    for (int i = 0; i < n - 1; ++i) {
        idx = LF[idx];
        res += L[idx];
    }
    reverse(res.begin(), res.end());
    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}
