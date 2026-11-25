#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define MOD 1000000007

int exp(int b, int e)
{
    if(e==0) return 1;
    int res=exp(b,e/2);
    res = (res*res)%MOD;
    if (e%2==1) return (res*b)%MOD;
    return res;
}

//! Some important concept known as burnside lemma
signed main()
{
    int n,m; cin>>n>>m;
    int ans=0;
    for(int i=0; i<n; ++i)
    {
        int k=__gcd(i,n);
        ans+=exp(m,k);
        ans%=MOD;
    }
    ans*=exp(n,MOD-2); // Have to divide ans by n
    ans%=MOD;
    cout << ans << endl;
    return 0;
}
