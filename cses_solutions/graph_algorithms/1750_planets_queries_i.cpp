#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n,m; cin>>n>>m;
	// vector<vector<int>> up(n+1, vector<int>(35));
	int up[n+1][35];
	for (int i=1; i<=n; ++i) {cin >> up[i][0];}
	
	// Build the table
	for (int j=1; j<35; ++j){
		for(int i=1; i<=n; ++i){
			up[i][j] = up[up[i][j-1]][j-1];
		}
	}
	
	int node, steps; 
	for(int i=0; i<m; ++i){
		cin >> node >> steps;
		int ans = node;
		
		for(int i=0; i<35; ++i){
			if (((1ll<<i) & steps) != 0){
				ans = up[ans][i];
			}
		}
		cout << ans << endl;
	}
	
	return 0;
}
