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
	// Removal Game
	// Learning from Hitesh Tripathi
	// Main note. 
	// If we are aiming to maximise the score of p1.
	// We are also trying to maximise the value of p1-p2 
	// Since p1+p2 = const = sum of all elements in the array 
	// The result of current choice affects the further states
	// That is where dp comes in
	// Hint : n2 approach is possible 
	// This will be very interesting since we will only fill the lower triangle of dp matrix
	// dp[i][j] = max(p1-p2) with numbers from i to j
	// dp[i][i] = a[i].
	// This is the base case
	// After this, start from dp[0][0]
	// dp[i][j] = max((a[i]-dp[i+1][j]),(a[j]-dp[i][j-1])); 
	// This is god level !
	int n; cin>>n;
	int a[n+1] = {0};
	int t=0;
	for (int i=1; i<=n; ++i)
	{
		cin>>a[i];
		t += a[i];
	}
	// Get into the dp formation
	int dp[n+1][n+1];
	// This nested loop is the most brainy part
	for(int i=n; i>=1; --i)
	{
		for (int j=i; j<=n; ++j) // Note how j is declared
		{
			if (i==j)
			{
				dp[i][j] = a[i];
			}
			else
			{
				dp[i][j] = max((a[i]-dp[i+1][j]),(a[j]-dp[i][j-1]));
			}
		}
	}
	cout << (dp[1][n]+t)/2 << endl;
	return 0;
}
