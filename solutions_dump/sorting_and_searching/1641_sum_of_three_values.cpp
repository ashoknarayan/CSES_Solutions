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
    pair<int,int> v[n];
    for (int i=0; i<n; ++i)
    {
        int e; cin>>e;
        v[i] = {e,i+1};
    }

    sort(v,v+n);

    for (int i=0; i<n; ++i)
    {
        int l=i+1;
        int r=n-1;
        while(l<r)
        {
            int t = v[i].first + v[l].first + v[r].first;
            if (t<x){l++;}
            else if (t>x){r--;}
            else
            {
                cout << v[i].second << " ";
                cout << v[l].second << " ";
                cout << v[r].second << endl;
                return 0;
            }
        }
    }
    cout << "IMPOSSIBLE" << endl;
    return 0;
}
