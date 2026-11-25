#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int mod = 1e9+7;

void solve(){
    int n; cin>>n;
    vector<int> dp(n+1,0); dp[0] = 1;
    for (int i=1; i<=n; ++i){
        for (int j=1; j<=6; ++j){
            if (i-j >= 0){
                dp[i] += dp[i-j];
                dp[i] %= mod;
            }
        }
    }
    cout << dp[n] << endl;
    return;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); int t=1;
    //  cin >> t;
    while(t--) solve();
    return 0;
}
