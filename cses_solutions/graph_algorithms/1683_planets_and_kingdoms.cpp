#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

// Planets and Kingdoms
// I am copying from Codenzyme.
// Also trying to learn it too.
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
	reverse(topo.begin(), topo.end());


	vector<bool> VIS(n+1,false);
	vector<int> scc(n+1,0);
	function<void(int,int)> dfs2 = [&](int node, int colour)
	{
		VIS[node] = true;
		scc[node] = colour;
		for(int c:G[node])
			if (!VIS[c])
				dfs2(c,colour);
	};

	// We are storing one node from each of the SCC

	int colour = 0;
	for (int i:topo)
    {
		if (!VIS[i])
			++colour, dfs2(i,colour);
    }

    cout << colour << endl;
	for (int k=1; k<=n; ++k)
        cout << scc[k] << " ";
    cout << endl;
	return 0;
}


// I have tried to learn it as far as I can.
// But I have not understood it completely.
// Will submit and then try to learn further.
