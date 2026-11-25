#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int mod = 1e9+7;

void solve(){
    int n,k; cin>>n>>k;
    vector<int> a(n); for(int &i:a) cin>>i;
    vector<int> dp(k+1,INT_MAX); dp[0] = 0;
    for(int i=1; i<=k; ++i){
        for(int j:a){
            if (i-j >= 0){
                dp[i] = min(dp[i], dp[i-j]+1);
            }
        }
    }
    cout << (dp[k] == INT_MAX ? -1:dp[k]) << endl;
    return;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); int t=1;
    //  cin >> t;
    while(t--) solve();
    return 0;
}
