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
    int n,k; cin>>n>>k;
    vector<pair<int,int>> inp(n);
    for (int i=0; i<n; ++i)
    {
        cin >> inp[i].second >> inp[i].first;
    }
    // Sort this !
    sort(inp.begin(),inp.end());
    // Transfer the first k ending times to seto of k
    seto<pair<int,int>> kp;
    int ans = 0;
    for (int i=0; i<n; ++i)
    {
        auto r = kp.order_of_key({inp[i].second +1, -1});
        if (r==0 && kp.size()<k)
        {
            kp.insert({inp[i].first , i});
            ans++;
        }
        else if (r!=0)
        {
            auto x = kp.find_by_order(r-1);
            kp.erase(x);
            kp.insert({inp[i].first , i});
            ans++;
        }
        // Note that we are not just assignning the first k values of input, 
        // We have to optimise in that too.
        // Let's see if that works 
    }
    cout << ans << endl;
    return 0;
}
