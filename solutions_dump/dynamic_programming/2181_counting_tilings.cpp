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

int til[1001][1<<10]; 	// dp array format dp[m][2^n] 
int n,m; 				// Global Variables since I need them in recursive function

// This is the main recursive function
void fill_column(int c, int idx, int curr_k, int next_k)
{
	if (idx==n) // Breaking Condition
	{
		til[c+1][next_k] += til[c][curr_k];
		til[c+1][next_k] %= mod;
		return;
	}

	if (curr_k & (1<<idx))   // Check if the current tile is full
	{
		fill_column(c,idx+1,curr_k,next_k);
	}
	else
	{
		// Add a horizontal tile
		fill_column(c,idx+1,curr_k,next_k|(1<<idx));
		// That or is to set the position to 1 since the horizontal tile covers idx position of next_k mask too !

		// Now is a vertical tile possible ? 
		// For that I need 
			// idx <= n-2
			// next tile also must be empty 
		if (idx<=n-2 && (!(curr_k & (1<<idx+1))))
		{
			fill_column(c,idx+2,curr_k,next_k);
		}
	}

}
// This is the main recursive function

signed main()
{
	cin>>n>>m;
	til[0][0]=1; 						// <- have no idea why this is so
	for (int c=0; c<m; ++c) 			// Iterate through columns {m}
		for (int k=0; k<(1<<n); ++k)	// iterate through all MASKS
			if (til[c][k]>0)
				fill_column(c,0,k,0);	// This will fill all the possibilities for that column and that mask
	cout << til[m][0] << endl;
	return 0;
}


// Counting Tilings Problem
// Learnt from NEATLY STRUCTURED
// Guarentee -> This is TOUGH + Counter Intutive
