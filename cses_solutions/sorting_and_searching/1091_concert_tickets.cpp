#include <bits/stdc++.h>
using namespace std;
#define int long long
 
signed main()
{
    int n,m; cin>>n>>m;
    set <pair<int,int>> h;
    for (int i=0; i<n; ++i)
    {
        int e; cin>>e;
        h.insert({e,i});
    }

    for (int i=0; i<m; ++i)
    {
        int t; cin>>t;
        auto r = h.lower_bound({t+1,0});

        if (r==h.begin()){cout << -1 << endl;}
        else
        {
            r--;
            cout << (*r).first << endl;
            h.erase(r);
        }
    }
    return 0;
}
