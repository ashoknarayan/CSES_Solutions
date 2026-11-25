#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define int long long
#define endl '\n'

template <typename T>
using seto = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


signed main()
{
    int x,n; cin>>x>>n;

    set<int> s;
    map<int,int> m;
    
    s.insert(0); s.insert(x);
    m[x]=1;

    for (int i=0; i<n; ++i)
    {
        int e; cin>>e;
        auto uit = s.upper_bound(e);
        int u = *uit;
        int l = *(prev(uit));
        s.insert(e);

        m[u-l]--;
        if (m[u-l]==0){m.erase(u-l);}

        // Add u-e
        if (m.find(u-e)==m.end()){m[u-e]=1;}
        else {m[u-e]++;}

        // Add e-l
        if (m.find(e-l)==m.end()){m[e-l]=1;}
        else {m[e-l]++;}

        cout << m.rbegin()->first << endl;
    }
    return 0;
}

