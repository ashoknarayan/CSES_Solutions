#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using oset =tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update> ;
#define endl "\n"
#define int  long long
#define fio ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
 
signed main()
{
    int n,k; cin>>n>>k;
    int a[n];
    for (int i=0; i<n; ++i){cin>>a[i];}
    oset<pair<int,int>> o;
    for (int i=0; i<k; ++i)
    {
        o.insert({a[i],i});
    }
    cout << (o.find_by_order((k-1)/2))->first << " ";
    for (int i=k; i<n; ++i)
    {
        o.erase ({a[i-k],i-k});
        o.insert({a[i-0],i-0});
        cout << (o.find_by_order((k-1)/2))->first << " ";
    }
    cout << endl;
    return 0;
}
