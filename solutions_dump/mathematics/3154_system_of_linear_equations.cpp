#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int MOD = 1e9 + 7;

int modinv(int a) {
    int res = 1, b = MOD - 2;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int n, m;
vector<vector<int>> mat;

void solve() {
    cin >> n >> m;
    mat.assign(n, vector<int>(m + 1));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= m; ++j)
            cin >> mat[i][j];

    int row = 0;
    for (int col = 0; col < m && row < n; ++col) {
        int sel = -1;
        for (int i = row; i < n; ++i)
            if (mat[i][col]) {
                sel = i;
                break;
            }
        if (sel == -1) continue;
        swap(mat[row], mat[sel]);

        int inv = modinv(mat[row][col]);
        for (int j = col; j <= m; ++j)
            mat[row][j] = mat[row][j] * inv % MOD;

        for (int i = 0; i < n; ++i) {
            if (i != row && mat[i][col]) {
                int factor = mat[i][col];
                for (int j = col; j <= m; ++j)
                    mat[i][j] = (mat[i][j] - factor * mat[row][j] % MOD + MOD) % MOD;
            }
        }
        ++row;
    }

    // Check for inconsistency
    for (int i = row; i < n; ++i)
        if (mat[i][m]) {
            cout << -1 << endl;
            return;
        }

    // Back-substitute
    vector<int> res(m);
    for (int i = 0; i < row; ++i) {
        int j = 0;
        while (j < m && mat[i][j] == 0) ++j;
        if (j == m) continue;
        res[j] = mat[i][m];
    }
    for (int x : res) cout << x << ' ';
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}
