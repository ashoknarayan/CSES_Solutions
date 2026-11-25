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
    int n; cin>>n;
    while(n--)
    {
        int a,b,m;
        cin>>a>>b;
        //if (a==0 && b==0){cout << 1 << endl; continue;}
        m = 1e9+7;
        int ans=1;
        while(b>0) 
        {
            if (b%2==1){ans*=a;ans%=m;}
            b = b>>1;
            a = (a*a)%m;
        }
        cout << ans << endl;
    }
    return 0;
}
