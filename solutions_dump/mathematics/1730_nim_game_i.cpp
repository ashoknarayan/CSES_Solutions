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
            ans = ans^e;
        }
        if (ans) cout << "first" << endl;
        else cout << "second" << endl;
    }
    return 0;
}

/*!
Nims game is a topic in Game Theory.
This is the simplest version !
And if XOR of all =0 -> Player loses
Else he wins
*/
