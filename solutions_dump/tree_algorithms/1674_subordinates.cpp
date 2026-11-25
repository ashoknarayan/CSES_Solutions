#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define endl '\n'
#define MOD 1000000007
 
 
vector<int> c(200001,0);
vector<int> g[200001];
 
 
int dfs(int node)
{
    for(int child:g[node])
        c[node]+=dfs(child)+1;
    return c[node];
}
 
 
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; cin>>n;
    int e; 
    for (int i=2; i<=n; ++i)
    {
        cin>>e;
        g[e].push_back(i);
    }
    dfs(1);
    for (int i=1; i<=n; ++i)
        cout << c[i] << " ";
    return 0; 
}
