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
    int n; cin>>n; int k=1; // That's all !
    seto<int> J;
    for (int i=1; i<=n; ++i){J.insert(i);}

    // Untill J gets empty
    int p=0;
    while(!J.empty())
    {
        p+=k;
        p%=J.size();
        auto i = J.find_by_order(p);
        cout << *i << " ";
        J.erase(i);
    }
    return 0;
}
