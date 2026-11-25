#include<bits/stdc++.h>
using namespace std;

int MOD = 1000000007;



int main(){
	int n; cin>>n;
	
	vector<vector<int>> dp(n+1, vector<int>(n+1,0));
	
	// Get input
	for (int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			char x; cin>>x;
			if (x == '*') dp[i][j] = -1;
		}
	}
	
	if (dp[1][1] == -1) {cout << 0 << endl; return 0;}
	
	dp[1][1] = 1;
	
	
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			if (i==1 && j==1) continue;
			if (dp[i][j] == -1) continue;
			
			int up = dp[i-1][j];
			if (up==-1) up=0; // 0 ways if you can not reach here
			int lt = dp[i][j-1];
			if (lt==-1) lt=0;
			
			dp[i][j] = (up+lt)%MOD;
		}
	} 
	
	cout << ( dp[n][n] == -1 ? 0 : dp[n][n]);
	return 0;
}
