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
	int n;
	cin>>n;
	cout << n << " ";
	while (n!=1)
	{
		if (n%2==1){n=3*n+1;}
		else {n/=2;}
		cout << n << " ";
	}
	cout << endl;
	return 0;
}
