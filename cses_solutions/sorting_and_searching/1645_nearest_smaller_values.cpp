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
    // Nearest smaller Left
    // Learnt from online 
    // Excellent Solution
    // https://www.youtube.com/watch?v=NIiK0ycMkmE

    int n; cin>>n;
    int a[n];
    for (int i=0; i<n; ++i) cin>>a[i];
    int b[n]; b[0]=-1;
    for (int i=1; i<n; ++i)
    {
        int j=i-1;
        while (true)
        {
            if (a[i]<=a[j] && j!=-1)
            {
                j=b[j];
            }
            else
            {
                b[i]=j;
                break;
            }
        }
    }
    for (auto x:b){cout << x+1 << endl;}

    return 0;
}
