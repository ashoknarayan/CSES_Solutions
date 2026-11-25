#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,x; cin>>n>>x; vector<int> dp(x+1), pg(n), pr(n);
    for (int&i:pr) cin>>i; for(int&i:pg) cin>>i;
    for(int i=0; i<n; ++i) for(int j=x; j>=pr[i]; --j)
        dp[j] = max(dp[j], dp[j-pr[i]] + pg[i]);

    cout << dp[x] << '\n';
    return 0;
}
