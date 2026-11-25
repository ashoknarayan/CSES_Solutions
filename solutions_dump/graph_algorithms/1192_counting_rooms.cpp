#include<bits/stdc++.h>
using namespace std;


int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n,m; cin>>n>>m;
	vector<vector<bool>> grid(n+2, vector<bool>(m+2, false));
	
	char x;
	for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j){
		cin >> x;
		if (x == '.') grid[i][j] = true;
	}
	
	vector<vector<int>> dir = {{1,0},{0,1},{-1,0},{0,-1}};
	pair<int,int> dad, kid;
	
	int ans = 0;
	for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) if (grid[i][j]) {
		// Kill the clan
		++ans;
		stack<pair<int,int>> st;
		st.push({i,j});
		grid[i][j] = false;
		
		while(!st.empty()){
			dad = st.top();
			grid[dad.first][dad.second] = false;
			st.pop();
			for (vector<int> k : dir){
				kid.first = dad.first + k[0];
				kid.second = dad.second + k[1];
				if (grid[kid.first][kid.second]){
				//	grid[kid.first][kid.second] = false;
					st.push(kid);
				}
			}
		}
		
		
	}
	
	cout << ans << endl;
	
}
