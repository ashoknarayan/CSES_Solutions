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
    int n,q; cin>>n>>q;
    int a[n]; 
    for (int i=0; i<n; ++i){cin>>a[i];}
    for (int i=1; i<n; ++i){a[i]+=a[i-1];}
    for (int i=0; i<q; ++i)
    {
        int l,r; cin>>l>>r;
        l--; r--; 
        if (l==0){cout << a[r] << endl;}
        else {cout << a[r]-a[l-1] << endl;}
    }
}
