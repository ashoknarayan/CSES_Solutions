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
    int a,b; cin>>a>>b;
    vector<int> f(a+b); f[0]=1;
    for (int i=1; i<a+b; ++i)
        f[i] = (f[i-1]*i)%MOD;
    int ans = f[a+b-1];
    ans = (ans*exp(f[b  ],MOD-2))%MOD;
    ans = (ans*exp(f[a-1],MOD-2))%MOD; // Inverse of factorials
    //! There is some complex math involved. Just rem n+r-1 C r-1 formula
    cout << ans << endl;
    return 0;
}
