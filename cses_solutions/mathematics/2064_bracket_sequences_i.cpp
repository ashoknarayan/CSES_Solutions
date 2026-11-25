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
    // Bracket Sequences
    //! Catalan Numbers (1/k+1)*(2k)C(k)
    // Also none exist if n is odd
    int n; cin>>n;
    if(n%2==1)
    {
        cout << 0 << endl;
        return 0;
    }
    n/=2;
    int f[2*n+1]; f[0]=1;
    for (int i=1; i<=2*n; ++i)
        f[i] = (f[i-1]*i)%MOD;
    int ans = f[2*n];
    ans *= exp(f[n  ],MOD-2); ans%=MOD;
    ans *= exp(f[n+1],MOD-2); ans%=MOD;
    cout << ans << endl;
    return 0;
}


