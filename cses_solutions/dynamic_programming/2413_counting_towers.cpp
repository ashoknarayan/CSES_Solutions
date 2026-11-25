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
	// I learnt completely from TLE Eliminators 
	// Check the pic at 17:08 in the video 
	// https://youtu.be/ZeRewE1Ks5Q?t=1028
	// Now lets get to work 
	// I will have 2 dp arrays (2thin) and (1fat)
	// tt[n] and f[n] . This is a pic representation of the states 
		// Now from the picture you can tell this ! 
		// To determine the tt[i+1] and f[i+1] from tt[i] and f[i]
		// tt[i+1] = 4*tt[i] + 1*f[i]
		// f [i+1] = 1*tt[i] + 2*f[i]
	// Base Case ? 
	// tt[0] = 1; 
	// f [0] = 1;
	// That's all !
	
	// I have an idea! 
	// Instead of calculating for all testcases 
	// We can store the answer for all n till 10^6
	// And then for each testcase, we can output the value at that index
	
	// First get the answer array for all of n
	int tt[1000001]; tt[1] = 1;
	int f [1000001]; f [1] = 1;
	int a [1000001]; a [1] = 2;
	for (int i=2; i<=1000000; ++i)
	{
		tt[i] = 4*tt[i-1] + 1*f [i-1];
		f [i] = 1*tt[i-1] + 2*f [i-1];
		a [i] = 1*tt[i  ] + 1*f [i  ];

		tt[i]%=mod;
		f [i]%=mod;
		a [i]%=mod;

	}
	// Now lets get into the main code ! 
	
	int t; cin>>t;
	for(int i=0; i<t; ++i)
	{
		int n; cin>>n;
		cout << a[n] << endl;
	}

	return 0;
}

