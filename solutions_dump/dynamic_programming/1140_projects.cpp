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



// This was the exact same logic that I wanted to implement
// But I did not know how to implement it.
// This idea of making a struct is awesome !


struct p     // Project
{
	int s; // Start
	int e; // End
	int v; // Value
	
	// when sort function is called, it will sort them on the basis of their end times in asc order 
	// That is the meaning of this bool operator < here
	bool operator <(const p& other)const
	{
		return e < other.e;
	}
};


signed main()
{	
	// Projects Question 

	int n; cin>>n;
	vector<p> pr(n);
	for (int i=0; i<n; ++i)
	{
		cin >> pr[i].s >> pr[i].e >> pr[i].v;
	}
	sort (pr.begin(),pr.end());
	
	set<pair<int,int>> ends;
	ends.insert({0,0});
	
	int ans = 0;
	
	for (int i=0; i<n; ++i)
	{
		auto t = ends.lower_bound({pr[i].s , -1});
		t--;
		ans = max(ans,(pr[i].v + t->second));
		ends.insert({pr[i].e , ans});
	}
	
	cout << ans << endl;
	return 0;
}










