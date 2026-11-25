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
    string s; cin>>s;
    int n=s.size();
    vector<int> a(26,0);
    for (char c:s)
        a[c-'a']++;
    vector<int> f(n+1); f[0]=1;
    for (int i=1; i<=n; ++i)
        f[i] = (f[i-1]*i)%MOD;
    int ans = f[n];
    for (int x:a)
        ans = (ans*exp(f[x],MOD-2))%MOD;
    cout << ans << endl;
    return 0;
}

// I am trying this myself
