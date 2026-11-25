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
    // Reading Books 
    int n; cin>>n;
    int s=0;
    int m=0;
    for (int i=0; i<n; ++i)
    {
        int e; cin>>e;
        s+=e;
        m = max(e,m);
    }
    // I learnt completely from online.
    // Will try to work on this again
    cout << max (s,2*m) << endl;
    return 0;
}
