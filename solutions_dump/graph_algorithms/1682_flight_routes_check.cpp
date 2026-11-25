#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
// Flight Routes Check. 
// We need to check if the entire graph is 1 single SCC

signed main()
{
	int n,m; cin>>n>>m;
	vector<int> g[n+1];
	vector<int> G[n+1]; // Reverse Graph 
	int u,v;
	for (int i=0; i<m; ++i)
	{
		cin>>u>>v;
		g[u].push_back(v);
		G[v].push_back(u);
	}
	// I need to get the topological Sort. 
	// I will make a function inside the main only.
	vector<bool> vis(n+1,false);
	vector <int> topo;
	function<void(int)> dfs = [&](int node)
	{
		vis[node] = true;
		for(int c:g[node])
			if (!vis[c]) 
				dfs(c);
		topo.push_back(node);
	};
	for (int i=1; i<=n; ++i)
		if (!vis[i])
			dfs(i);
			// I will obtain the topological sort in the reverse order.
	reverse(topo.begin(), topo.end());
	// We will ignore the backedge. [else topo sort wont even exist]
	// Now for G [reverse graph]
	vector<bool> VIS(n+1,false);
	function<void(int)> dfs2 = [&](int node)
	{
		VIS[node] = true;
		for(int c:G[node])
			if (!VIS[c]) 
				dfs2(c);
	};
	
	// We are storing one node from each of the SCC
	vector<int> scc;
	for (int i:topo)
		if (!VIS[i])
			scc.push_back(i), dfs2(i);

	if (scc.size()>1)
	{
		cout << "NO" << endl;
		cout << scc[1] << " " << scc[0] << endl;
		// Note that there may be a path from scc[0] to scc[1].
		// We are working with the reverse graph in the SCC Section.
		// Therefore scc[1] -> scc[0] is printed
	}
	else
	{
		cout << "YES" << endl;
	}
	return 0;
}
