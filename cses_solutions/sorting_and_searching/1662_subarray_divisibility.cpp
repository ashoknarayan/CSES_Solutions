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
    int c=0;
    int a[n]={0}; a[0]=1;
    int s=0;
    for (int i=0; i<n; ++i)
    {
        int e; cin>>e;
        s+=e;
        int r = (s%n +n)%n;
        c+=(a[r]);
        a[r]++;
    }    
    cout << c << endl;
}
