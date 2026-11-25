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
    int n; cin>>n;
    map<int,int> m;
    for(int i=0; i<n; ++i)
    {
        int a,b; cin>>a>>b;
        if (m.find(a)==m.end()){m[a]=1;}
        else {m[a]++;}
        if (m.find(b)==m.end()){m[b]=-1;}
        else {m[b]--;}
    }

    int t=0;
    int a=0;

    for (auto x:m)
    {
        t+=x.second;
        a=max(t,a);
    }
    cout << a << endl;
    return 0;
}

