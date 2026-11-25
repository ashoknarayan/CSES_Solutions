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
    int l=0;
    for (int i=0; i<n; ++i)
    {
        cin>>a[i];
        l=max(l,a[i]);
    }
    int r=1e15;
    int m;
    int ma=1e15;
    // We need to take the min value of m 
    // m is the maximum sum in each case
    while(l<=r)
    {
        m=(l+r)/2;
        int t=1;
        int s=0;
        for(auto x:a)
        {
            if (s+x > m)
            {
                s=0; 
                t++;
            }
            s+=x;
        }

        if (t>k)
        {
            l=m+1;
            continue;
        }
        if (t<=k)
        {
            r=m-1;
            ma = min(ma,m);
            continue;
        }
    }
    cout << ma << endl;
    return 0;
}
