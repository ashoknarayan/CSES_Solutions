#include<bits/stdc++.h>
using namespace std;
 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    int n,m; cin>>n>>m; vector<vector<int>> g(n+1); vector<int> ind(n+1,0);
    int a,b; for(int i=0; i<m; ++i){cin>>a>>b; g[a].push_back(b); ind[b]++;}
    
    vector<int> ans;
    queue<int> q; for (int i=1; i<=n; ++i) if (!ind[i]) q.push(i);
 
    int dad;
    while(!q.empty()){
        dad = q.front(); q.pop();
        ans.push_back(dad);
        for (int cc:g[dad]) {ind[cc]--; if (!ind[cc]) q.push(cc);}
    }
    vector<int> dp(n+1,0);
    dp[1]=1;

    for(int u:ans)
        for (int cc : g[u])
            dp[cc] = (dp[cc]+dp[u])%1000000007;

    cout << dp[n] << '\n';
    return 0;
}
