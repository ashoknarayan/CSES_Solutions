#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

signed main()
{
    int n; cin>>n;
    set<pair<int,int>> s;
    int t=0;

    for (int i=0; i<n; ++i)
    {
        int e; cin>>e;
        auto u = s.upper_bound({e,i});
        if(u==s.end()){t++;}
        else{s.erase(u);}
        s.insert({e,i});
    }
    cout << t << endl;
    return 0;
}
