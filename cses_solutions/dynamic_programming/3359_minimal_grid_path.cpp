#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>

int n;
vector<string> grid;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    grid.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> grid[i];

    vector<pii> curr = {{0, 0}};
    string res;
    res += grid[0][0];

    vector<vector<bool>> vis(n, vector<bool>(n, false));
    vis[0][0] = true;

    for (int step = 1; step <= 2 * n - 2; ++step) {
        char best = 'Z' + 1;
        vector<pii> next;

        for (auto [x, y] : curr) {
            if (x + 1 < n && !vis[x+1][y])
                best = min(best, grid[x + 1][y]);
            if (y + 1 < n && !vis[x][y+1])
                best = min(best, grid[x][y + 1]);
        }

        for (auto [x, y] : curr) {
            if (x + 1 < n && grid[x + 1][y] == best && !vis[x+1][y]) {
                next.push_back({x + 1, y});
                vis[x+1][y] = true;
            }
            if (y + 1 < n && grid[x][y + 1] == best && !vis[x][y+1]) {
                next.push_back({x, y + 1});
                vis[x][y+1] = true;
            }
        }

        res += best;
        curr = move(next); // Move to reuse memory
    }

    cout << res << '\n';
}
