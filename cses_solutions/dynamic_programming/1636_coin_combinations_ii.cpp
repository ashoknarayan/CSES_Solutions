#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    int x; cin>>x;
    vector<int> coins(n); for(int&i:coins) cin>>i;
    vector<int> dp(x+1,0); dp[0] = 1;
    
    for(int coin : coins){
        for(int i=1; i<=x; ++i){
            if (i-coin >=0){
                dp[i]+=dp[i-coin];
                dp[i]%=1000000007;
            }
        }
    }
    cout << dp[x] << '\n';
}
