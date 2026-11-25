#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define mod 1000000007
signed main(){
    int n,m; cin>>n>>m;
    vector<int> a(n+1);
    for (int i=0; i<n; ++i){
        cin>>a[i+1];
    }
    vector<vector<int>> dp(n+1, vector<int> (m+1,0));
    if (a[1]!=0){
        dp[1][a[1]]=1;
    } else {
        for (int i=1; i<=m; ++i){
            dp[1][i]=1;
        }
    }

    for (int i=2; i<=n; ++i){
        if (a[i]!=0){
            int j=a[i];
            // dp[i][j] += dp[i-1][j-1]+dp[i-1][j]+dp[i-1][j+1]
            if(j>1){dp[i][j] += dp[i-1][j-1] %= mod;}
            if(true){dp[i][j] += dp[i-1][j] %= mod;}
            if(j<m) {dp[i][j]+=dp[i-1][j+1] %= mod;}
        } else {
            for (int j=1; j<=m; ++j){
                if(j>1){dp[i][j] += dp[i-1][j-1] %= mod;}
                if(true){dp[i][j] += dp[i-1][j] %= mod;}
                if(j<m){dp[i][j] +=dp[i-1][j+1] %= mod;}
            }
        }
    }
    int ans=0;
    for (int j=1; j<=m; ++j){
        ans+=dp[n][j]%=mod;
    }
    cout << ans%mod << endl;
            
    return 0;
}





    
