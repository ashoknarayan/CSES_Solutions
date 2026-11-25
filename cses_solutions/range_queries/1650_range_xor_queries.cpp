#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
signed main()
{
    int n,q; cin>>n>>q;
    int ps[n+1]; ps[0]=0; // The neutral element for XOR
    int e;
    for (int i=1; i<=n; ++i)
    {
        cin>>e;
        ps[i] = ps[i-1]^e;
    }
    int l,r;
    while(q--)
    {
        cin>>l>>r;
        cout << (ps[r]^ps[l-1]) << endl;
    }
    return 0;
}

// Just use the fact that, a^a = 0 and a^0 = a; So that helps a lot in this problem.
