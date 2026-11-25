#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define int long long
#define endl '\n'
#define mod 1000000007
 
template <typename T>
using seto = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
 
signed main()
{
	// Edit Distance 
	// 3 Possibilities
		// Insert
		// Remove
		// Change
	// Just watch the video of TLE Eliminators for this too.
	// IMP point ! -> If last 2 charecters are same then ignore them.
	// Otherwise this reduces each point to 3 cases
		// Replace last charecter if 1 string 
			// Symmetrical for both strings
		// Remove the last charecter of first  string 
		// Remove the lase charecter of second string
			// Not Symmetrical
			// But in 1 string, removing and adding are same since last char can be ignored

	string a,b; cin>>a>>b;
	int dp[a.size()+1][b.size()+1];
	// Base Case
	for (int i=0; i<=a.size(); ++i)
	{
		dp[i][0] = i;
	}
	for (int j=0; j<=b.size(); ++j)
	{
		dp[0][j] = j; 
	}
	// Get into the main code 
	for (int i=1; i<=a.size(); ++i)
	{
		for (int j=1; j<=b.size(); ++j)
		{
			dp[i][j] = dp[i-1][j-1]; // if a[i-1] == b[j-1]
			if (a[i-1] != b[j-1])    // Convert from 1 based to 0 based indexing 
			{
				// Compare out of
					// Replace 
					// Remove1
					// Remove2
				int v1 = dp[i][j];   //+1; // Here dp[i][j] still has value of dp[i-1][j-1]
				int v2 = dp[i-1][j]; //+1;
				int v3 = dp[i][j-1]; //+1; // Note that +1 is there everywhere
				dp[i][j] = min({v1,v2,v3}) +1;
			}			
		}
	}

	cout << dp[a.size()][b.size()] << endl;
	return 0;
}

