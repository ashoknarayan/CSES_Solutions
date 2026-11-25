#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> grid;
vector<string> ans;

char get_new_char(int x, int y) {
	set<char> used;
	used.insert(grid[x][y]); // must differ from original

	// check neighbors in answer grid
	for (int dx : {-1, 1}) {
		int nx = x + dx;
		if (nx >= 0 && nx < n) used.insert(ans[nx][y]);
	}
	for (int dy : {-1, 1}) {
		int ny = y + dy;
		if (ny >= 0 && ny < m) used.insert(ans[x][ny]);
	}

	for (char ch : {'A', 'B', 'C', 'D'}) {
		if (!used.count(ch)) return ch;
	}
	return '?'; // should never happen
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m;
	grid.resize(n);
	ans.assign(n, string(m, '?'));

	for (int i = 0; i < n; ++i) cin >> grid[i];

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			ans[i][j] = get_new_char(i, j);
			if (ans[i][j] == '?') {
				cout << "IMPOSSIBLE\n";
				return 0;
			}
		}
	}

	for (int i = 0; i < n; ++i) cout << ans[i] << '\n';
}
