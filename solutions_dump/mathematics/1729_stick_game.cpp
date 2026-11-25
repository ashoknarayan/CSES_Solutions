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
    //! This is very simple only.
    // Just normal DP Solution
    int n; cin>>n;
    int k; cin>>k;
    int P[k];
    vector<char> ans(n+1,'L');
    for (int i=0; i<k; ++i)
    {
        cin>>P[i];
        ans[P[i]] = 'W';
    }

    for (int i=1; i<=n; ++i)
        for (int p:P)
            if (p<i && ans[i-p] == 'L')
                {ans[i]='W'; break;}

    for (int i=1; i<=n; ++i)
        cout << ans[i];
    cout << endl;
    return 0;
}
