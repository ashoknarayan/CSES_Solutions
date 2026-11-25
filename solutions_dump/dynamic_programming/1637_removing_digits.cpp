#include<bits/stdc++.h>
using namespace std;

vector<int> dp(1000000+5, -1); // If -1 then ans has not been calculated

int fn(int n){
	if (dp[n]!=-1) return dp[n];

	string s = to_string(n);
	
	int ans = INT_MAX;
	
	for (char i:s){
		int digit = i-'0';
		if (digit!=0) { ans = min(ans, 1+fn(n-digit)); }
	}
	
	dp[n] = ans; // update dp, then use it 
	return dp[n];
}

int main(){
	dp[0] = 0;
	int n; cin>>n; cout << fn(n) << endl;
	return 0;
}

// Removing Digits, recursive code
