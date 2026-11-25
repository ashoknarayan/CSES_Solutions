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
        for (int cc:g[dad]){
            ind[cc]--;
            if (!ind[cc]) {
                q.push(cc);
            }
        }
    }
 
    vector<int> dp(n+1,0);
    dp[1]=1;
    vector<int> par(n+1,0);
    for(int u:ans){
        for (int cc : g[u]){
            if (dp[u]!=0 && dp[cc] < dp[u]+1){
                dp[cc] = dp[u]+1;
                par[cc] = u;
            }
        }
    }
    if (dp[n] == 0){
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    vector<int> out = {n};
    int temp = n;
    while(temp != 1){
        temp = par[temp];
        out.push_back(temp);
    }
    cout << out.size() << endl;
    reverse(out.begin(), out.end());
    for (int i:out) cout << i << ' '; cout << endl;
    return 0;
}
