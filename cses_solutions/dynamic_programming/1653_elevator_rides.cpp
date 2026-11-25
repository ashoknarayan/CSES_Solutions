#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define int long long
#define endl '\n'
#define mod 1000000007
 
template <typename T>
using seto = tree<T, null_type, less<T>, 
rb_tree_tag, tree_order_statistics_node_update>;
void solve();

signed main()
{
	int n,x;
	cin>>n>>x;
	vector<int> w(n);
	for (int i=0; i<n; ++i)
	{
		cin>>w[i];
	}
	vector<pair<int,int>> dp(1<<n , {1e9,1e9});
	dp[0] = {1,0};
	for (int m=1; m<(1<<n); ++m)
	{
		for (int b=0; b<n; ++b)
		{
			if ((1<<b)&m) // -> that particular point has 1 in the bitmask !
			{
				int s = dp[m^(1<<b)].second; 
				// Choosing the value at m -> mask, such that it is 0 at bth position alone [XOR].
				pair <int,int> v;
				if (s+w[b] <= x)
				{
					v = { dp[m^(1<<b)].first +0 , s+w[b] }; // -> Accomodate in last ride itself
				}
				else
				{
					v = { dp[m^(1<<b)].first +1 , 0+w[b] }; // -> 1 more ride
				}

				// Each loop, replace with minimum
				dp[m] = min(dp[m],v);
			}
		}
	}
	cout << dp[(1<<n)-1].first << endl;
	// This is very tough question. Just submit this and pass by~~
	return 0;
}

// Subsets for Size n => 2^n times
// This is excellent bitmask 
