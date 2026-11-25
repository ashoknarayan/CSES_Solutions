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
    // Tasks and Deadlines 
    int n; cin>>n;
    int pa=0; int na=0;
    int a[n];
    for (int i=0; i<n; ++i)
    {
        cin>>a[i];
        int b; cin>>b; pa+=b;
    }
    sort(a,a+n);
    for(int i=0; i<n; ++i)
    {
        na+= ((n-i)*(a[i]));
    }

    cout << pa-na << endl;
    return 0;
}
