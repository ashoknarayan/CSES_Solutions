#include <bits/stdc++.h>
using namespace std;
 
void justDoIt();
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    justDoIt();
    return 0;
}
 
const int MAX_N = 3000;
const int MAX_K = 26;
long long res[MAX_K];
string a[MAX_N];
int goUp[MAX_N];
int goDown[MAX_N];
int goLeft[MAX_N];
int goRight[MAX_N];
int bit[MAX_N + 1];
vector<int> events[MAX_N];
int n, k;
 
void solve(int si, int sj) {
    int ci = si;
    int cj = sj;
    memset(bit, 0, sizeof(bit));
    while (ci >= 0 && cj >= 0) {
        if (ci > 0 && a[ci][cj] == a[ci - 1][cj]) {
            goUp[cj]++;
            goDown[cj]--;
        }
        else {
            goUp[cj] = 0;
            int x = 0;
            while (ci + x < n && a[ci][cj] == a[ci + x][cj]) {
                x++;
            }
            goDown[cj] = x;
        }
        if (cj + 1 < n && a[ci][cj] == a[ci][cj + 1]) {
            goRight[ci]++;
            goLeft[ci]--;
        }
        else {
            goRight[ci] = 0;
            int x = 0;
            while (cj >= x && a[ci][cj] == a[ci][cj - x]) {
                x++;
            }
            goLeft[ci] = x;
        }
        int len1 = min(goLeft[ci], goUp[cj] + 1);
        int ni = ci - len1 + 1;
        events[ni].push_back(ci + 1);
        int len2 = min(goDown[cj], goRight[ci] + 1);
        int s = 0;
        for (int i = ci + len2; i > 0; i -= i & (-i)) {
            s += bit[i];
        }
        res[a[ci][cj] - 'A'] += len2 - s;
        for (auto pos: events[ci]) {
            for (int i = pos; i <= n; i += i & (-i)) {
                bit[i]++;
            }
        }
        events[ci].clear();
        ci--;
        cj--;
    }
}
 
void justDoIt() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        events[i].reserve(n);
    }
    for (int i = 0; i < n - 1; i++) {
        solve(i, n - 1);
    }
    for (int j = n - 1; j >= 0; j--) {
        solve(n - 1, j);
    }
    for (int i = 0; i < k; i++) {
        cout << res[i] << '\n';
    }
}
