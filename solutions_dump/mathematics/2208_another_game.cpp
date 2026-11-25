#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define MOD 1000000007

signed main()
{
    int tc; cin>>tc;
    while(tc--)
    {
        int ans=0;
        int n; cin>>n;
        int e;
        for (int i=0; i<n; ++i)
        {
            cin>>e;
            ans+=e%2; // Something with even numbers is helping yous
        }
        if (ans) cout << "first" << endl;
        else cout << "second" << endl;
    }
    return 0;
}

/*!
Another game also has a formula. and an idea.
Just note it down
*/
