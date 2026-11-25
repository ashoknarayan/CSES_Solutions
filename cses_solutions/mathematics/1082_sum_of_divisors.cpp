#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define MOD 1000000007

int nS(int n)
{
    int a,b;
    if (n%2==1)
    {
        a=n; b=(n+1)/2;
    }
    else
    {
        a=n/2; b=n+1;
    }
    return ((a%MOD)*(b%MOD))%MOD; // This is also to prevent OVERFLOW.
}

signed main()
{
    int n; cin>>n;
    int s=0;
    for (int x=1; (x*x)<=n; ++x)
    {
        int c = n/x +1 -x;
        s += (c%MOD)*x;
        s %= MOD;
        s += nS(n/x) - nS(x) +MOD;
        s %=MOD; // All this to prevent OVERFLOW
    }
    cout << s << endl;
    return 0;
}
