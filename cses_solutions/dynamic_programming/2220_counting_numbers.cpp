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

int s(int x, vector<int>& dp)
{
	if (x<1) 
		return (x==0) ? 1:0;
	string t = to_string(x);
	int res=0;
	for (int i=0; i<t.size(); ++i)
	{
		res+=dp[i];
	}
	int pre=0;
	for (int i=0; i<t.size(); ++i)
	{
		int dig = t[i]-'0';
		int dif = t.size() - (i+1);
		int bel = (pre<dig) ? dig-1 : dig;
		res+= (dig==0)? 0:bel*dp[dif];
		if (dig==pre)
			return res;
		pre = dig;
	}
	return res+1;	// +1 for the number itself 

}


signed main()
{
	int a,b; cin>>a>>b;
	vector<int> dp(19);
	dp[0]=1;
	int res=1;
	for(int i=1; i<19; ++i)
	{
		res*=9;
		dp[i]=res;
	}
	cout << s(b, dp)-s(a-1, dp) << endl;
	return 0;
}

/*
Counting Numbers CSES
Tip : ans[a,b] = ans[0,b] - ans[0,a-1]
Copied from Anthony Ngene
*/



