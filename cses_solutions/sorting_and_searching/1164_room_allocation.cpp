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
    fio;
    int n; cin>>n;
    oset <pair<int,int>> t;
    int ans=0;
    int a[n];
 
 
    set<array<int,3>> inp; 
    for (int i=0; i<n; ++i)
    {
        array<int,3> c;
        cin >> c[0] >> c[1];
        c[2]=i;
        inp.insert(c);
    }
 
    for (auto x:inp)
    {
        int l=x[0];
        int r=x[1];
        int i=x[2];
 
        
        int o = t.order_of_key({l,-1});
        if (o==0)
        {
            ans++;
            a[i]=ans;
            t.insert({r,ans});
        }
        else
        {
            auto p = t.find_by_order(o-1);
            int e = p->second;
            t.erase(p);
            a[i]=e;
            t.insert({r,e});
        }
        
    }
 
    cout << ans << endl;
    for (auto x:a) {cout << x << " ";}
    return 0;
}
