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

signed main()
{
    // Derangement problem
    int n; cin>>n;
    vector<int> f(n+1); f[0]=1;
    for (int i=1; i<=n; ++i)
        f[i] = (f[i-1]*i)%MOD;
    int ans=0;
    int tgl=-1;
    for (int i=0; i<=n; ++i)
    {
        tgl*=-1;
        ans += (tgl*(f[n]*exp(f[i],MOD-2)))%MOD;
        ans += MOD; ans%=MOD;
        //! +MOD, %MOD is done to prevent -ve ans!
    }

    cout << ans << endl;
    return 0;
}

// I am trying this myself









