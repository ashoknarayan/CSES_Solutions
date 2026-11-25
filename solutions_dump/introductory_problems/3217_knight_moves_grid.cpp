#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

const int INF = 1e9;
int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

void solve() {
	int n;
	cin >> n;

	vector<vector<int>> dp(n, vector<int>(n, -1));
	queue<pair<int, int>> q;

	dp[0][0] = 0;
	q.push({0, 0});

	while (!q.empty()) {
		auto [x, y] = q.front();
		q.pop();

		for (int k = 0; k < 8; ++k) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx >= 0 && ny >= 0 && nx < n && ny < n && dp[nx][ny] == -1) {
				dp[nx][ny] = dp[x][y] + 1;
				q.push({nx, ny});
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			cout << dp[i][j] << " ";
		cout << endl;
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	solve();
}
