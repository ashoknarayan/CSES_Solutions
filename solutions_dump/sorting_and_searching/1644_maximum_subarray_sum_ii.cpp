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
    // Previous submission was from Chat_GPT.
    // I learnt from that and I will try my own now 
    int n,a,b; cin>>n>>a>>b;
    int e[n+1]={0};
    // This is excellent idea so that we do not confuse indexes.
    for (int i=1; i<=n; ++i)
    {
        cin>>e[i];
        e[i]+=e[i-1]; // Construct the prefix sum on the go
    }
    seto<pair<int,int>> k;
    for (int i=a; i<=b; ++i)
        k.insert({e[i],i});
    // Now lets go for the operation
    // Note that we can go till n-a
    // Since (n-1) - (n-a) + 1  == a -> min length req

    int ans = LLONG_MIN;
    for (int i=0; i<=n-a; ++i)
    {
        ans = max(ans , ((k.rbegin()->first)-e[i]));
        k.erase({e[i+a],i+a});
        if (i+b+1 <= n)
            k.insert({e[i+b+1],i+b+1});
        // This gives a seperate space for first index and at the same time includes the last one too !
    }
    cout << ans << endl;
    return 0;
}
