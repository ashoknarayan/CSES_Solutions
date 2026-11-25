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
    int n,x; cin>>n>>x;
    int a[n];  
    int c=0;
    for (int i=0; i<n; ++i)
        {cin>>a[i];}
    int b[n]; b[0]=a[0];
    for (int i=1; i<n; ++i){b[i]=b[i-1]+a[i];}
    oset<pair<int,int>> t;
    for (int i=n-1; i>=0; --i)
    {
        t.insert({b[i],i});
        int A = t.order_of_key({b[i]+x+1,-1});
        int a = t.order_of_key({b[i]+x+0,-1});
        c+=(A-a);
    }
    // Now for 0
    
    int AA = t.order_of_key({x+1,-1});
    int aa = t.order_of_key({x+0,-1});
    c+=(AA-aa);

    if (x==0){c-=n;} // Just each index gets repeated twice
    
 
    cout << c << endl;
    
    return 0;
}
