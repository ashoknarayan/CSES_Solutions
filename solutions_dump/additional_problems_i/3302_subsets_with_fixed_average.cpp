#include <bits/stdc++.h>
using namespace std;
#define int long long
const int M=250000,mod=1e9+7;int A[M*2+1],*dp=A+M;
signed main(){
 ios::sync_with_stdio(0);cin.tie(0);
 int n,x;cin>>n>>x;vector<int>a(n);for(auto&i:a){cin>>i;i-=x;}
 dp[0]=1;
 for(auto v:a){
  if(v>=0)for(int j=M;j-v>=-M;j--)dp[j]=(dp[j]+dp[j-v])%mod;
  else for(int j=-M;j-v<=M;j++)dp[j]=(dp[j]+dp[j-v])%mod;
 }
 cout<<(dp[0]+mod-1)%mod;
}
