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
	// Two Sets II
	//
	int n; cin>>n;
	if (n%4==1 || n%4==2)
	{
		 cout << 0 << endl;
		 return 0;
	}
	int s = (n*(n+1))/4;
	vector <int> dp(s+1,0);
	dp[0] = 1;
	for (int j=1; j<=n; ++j)
	{
		for (int i=s; i>=j; --i) // You are going in reverse since you can use each element only once!!
		{
			if (i-j>=0)
			{
				dp[i] += dp[i-j];
				// Modular arithmetic 
				dp[i]%=mod;
			}
		}
	}
	// Inverse Modular Arithmetic to give dp[s]/2
	cout << (dp[s]*((mod+1)/2))%mod << endl;
	return 0;
}
