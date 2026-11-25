#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            vector<bool> used(2*n, false);
            
            // Check left in row
            for (int k = 0; k < j; ++k)
                used[grid[i][k]] = true;
                
            // Check above in column
            for (int k = 0; k < i; ++k)
                used[grid[k][j]] = true;
                
            // Find smallest unused number
            int x = 0;
            while (used[x]) ++x;
            grid[i][j] = x;
        }
    }
    
    // Output
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << grid[i][j] << " ";
        cout << endl;
    }
}


signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); int t=1;
	// cin>>t; 
	while(t--) solve();
	return 0;
}
