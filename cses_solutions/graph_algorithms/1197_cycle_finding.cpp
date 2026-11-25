#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define endl '\n'
 
int n,m;
vector<array<int,3>> edges;
vector<int> dist;
vector<int> par;
 
void Bellman_Ford()
{
    int x; 
    dist[1]=0;
    for (int i=1; i<=n; ++i)
    {
        x=-1;
        for (array<int,3> e:edges)
        {
            int u=e[0];
            int v=e[1];
            int d=e[2];
            if (((dist[u]+d) < dist[v]))
            {
                dist[v] = dist[u]+d;
                par[v] = u;
                x=v;
            }
        }
    }
    if (x==-1){
        cout << "NO" << endl;
        return;}
    
    // Cycle Exists;
    for (int i=0; i<n; ++i) x=par[x];
    vector<int> cycle;
    for (int v=x; ; v=par[v])
    {
        cycle.push_back(v);
        if (v==x && cycle.size()>1) break;
    }

    reverse(cycle.begin(),cycle.end());
    cout << "YES" << endl;
    for (int x:cycle)
        cout << x << " ";
    cout << endl;
    return;
    
}
 
signed main()
{
    cin>>n>>m;
    dist.resize(n+1,INT_MAX); // Allow some value greater too.
    par.resize(n+1,-1);    
    edges.resize(m);
    for (int i=0; i<m; ++i)
        cin>>edges[i][0]>>edges[i][1]>>edges[i][2];
    Bellman_Ford();
    return 0;       
}
 
/*
Here x is only important for the nth cycle. 
Also this gave very good clarity for the High Score Question
[Check the Danger() in last 2 submission]
*/
