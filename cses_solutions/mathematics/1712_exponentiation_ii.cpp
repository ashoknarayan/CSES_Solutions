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
        // For this we use Fermats Little Theorem !
        // (a^(p-1))%p = 1;
        // So that reduces the problem a lot !!

        int a,b,c,m; cin>>a>>b>>c;
        m = 1e9+7;
        int n = 1e9+6;
        // First do b^c;
        int d=1;
        while (c>0)
        {
            if (c%2==1){d*=b; d%=n;}
            c=c>>1;
            b = (b*b)%n;
        }

        // Now do it for a^d;
        int ans=1;
        while (d>0)
        {
            if (d%2==1){ans*=a; ans%=m;}
            d=d>>1;
            a = (a*a)%m;
        }

        cout << ans << endl;
    }
    return 0;
}
