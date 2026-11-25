#include <bits/stdc++.h>
using namespace std; 
#define ll long long
const int N=5005,M=70; ll MOD=1e9+7; 
vector<int>pr,v[N],bs; bool f[M+5];

ll pw(ll a,ll b){ll r=1;for(;b;b>>=1,a=a*a%MOD)if(b&1)r=r*a%MOD;return r;}

int main(){
  ios::sync_with_stdio(0);cin.tie(0);
  for(int i=2;i*i<=M;i++)if(!f[i])for(int j=i*i;j<=M;j+=i)f[j]=1;
  for(int i=2;i<=M;i++)if(!f[i])pr.push_back(i);
  int n;cin>>n;
  for(int i=1;i<=n;i++){
    int x;cin>>x;int m=0;
    for(int j=0;j<pr.size();j++)while(x%pr[j]==0)x/=pr[j],m^=1<<j;
    v[x].push_back(m);
  }
  ll c=0;
  for(int i=71;i<N;i++){
    if(v[i].size()==1)c++;
    else if(v[i].size()>1){
      c++;for(int j=1;j<v[i].size();j++)v[1].push_back(v[i][j]^v[i][0]);
    }
  }
  for(int x:v[1]){for(int y:bs)x=min(x,x^y);if(x)bs.push_back(x);}
  c=n-bs.size()-c;
  cout<<pw(2,c);
}
