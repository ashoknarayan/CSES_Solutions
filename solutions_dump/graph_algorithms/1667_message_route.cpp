#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define int  long long
 
vector<int>  g[100001];
vector<bool> vis(100001,false);
vector<int>  p(100001,-1);

signed main()
{
    int n,m; cin>>n>>m;
    int a,b; 
    for(int i=0; i<m; ++i){
        cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);}
    
    queue<int> q; q.push(1); vis[1]=true;
    while(q.size())
    {
        int node = q.front(); q.pop();
        for (int x:g[node])
        {
            if(!vis[x])
            {
                vis[x]=true;
                q.push(x);
                p[x]=node;
            }
        }
    }
    if (p[n]==-1){cout << "IMPOSSIBLE" << endl; return 0;}
    vector<int> path; int node=n;
    while(node!=-1)
    {
        path.push_back(node);
        node=p[node];
    }
    reverse(path.begin(),path.end());
    cout << path.size() << endl;
    for (int x:path) cout << x << " ";
    return 0; 
}

/*
Shortest path on a undirected, unweighted graph.
BFS is the best.
*/

