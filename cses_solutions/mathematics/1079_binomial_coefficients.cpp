#include <bits/stdc++.h>
using namespace std;
#define int long long

// For nCr we need exp, factorial, Choose functions
//  So I will bind all 3 functions in one.
int MOD = 1e9+7;
vector<int> f(1000001); bool fdone=false;
int exp(int a, int b) {
    int ans=1;
    while(b){
        if (b%2==1){ans*=a;ans%=MOD;}
        b = b>>1;
        a = (a*a)%MOD;}
    return ans;}
int Choose(int n, int r){
    if (!fdone){f[0]=1;
    for(int i=1;i<=1000000;++i)f[i]=(f[i-1]*i)%MOD;fdone=true;}
    int ans = f[n];
    ans *= exp(f[r  ],MOD-2); ans%=MOD;
    ans *= exp(f[n-r],MOD-2); ans%=MOD;
    return ans;}


signed main()
{
    int t; cin>>t;
    int n,r;
    while(t--)
    {
        cin>>n>>r;
        cout << Choose(n,r) << endl;
    }
    return 0;
}
