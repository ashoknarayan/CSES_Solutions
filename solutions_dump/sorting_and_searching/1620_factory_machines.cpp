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
    fio;
    int n,t; cin >> n >> t;
    int m[n];
    for (int i=0; i<n; ++i){cin>>m[i];}

    // Use binary search to get the correct time !! 
    // That's all.

    int l=0;
    int r=1e18; // Note it is 1e9 * 1e9
                // This is since you can have the biggest product and the worst machine

    int tm=-1;

    while(l<=r)
    {
        int mid = (l+r)/2;
        int tt=0;
        for (auto x:m)
        {
            tt+=(mid/x);
            if (tt>=t){tm=mid; break;}
        }
        if (tm==mid){r=mid-1;}
        else{l = mid+1;}
    }

    cout << tm << endl;
    return 0;
}
