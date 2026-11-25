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
    for (int i=0; i<n; ++i)
    {
        cin>>a[i];
    }
    map<int,int> m;
    int j=0;
    int ans=0;
    for (int i=0; i<n; ++i)
    {
        // Inserting the value
        if (m.find(a[i])==m.end()){m[a[i]]=1;}
        else{m[a[i]]++;}
        // Finding the optimal j
        if (m.size()>k)
        {
            while(m.size()>k)
            {
                m[a[j]]--;
                if (m[a[j]]==0){m.erase(a[j]);}
                j++;
            }
        }
        ans += (i-j+1);
    }
    cout << ans << endl;
    return 0;
}
