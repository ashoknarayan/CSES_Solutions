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
            if (i>0 && i%2==1) // This is the condition thats all
                ans ^=(e);
        }
        if (ans) cout << "first" << endl;
        else cout << "second" << endl;
    }
    return 0;
}

/*!
This is the staircase NIM !
This also has a special result.
Just learn for now.
You can get into the derivation later

*/
