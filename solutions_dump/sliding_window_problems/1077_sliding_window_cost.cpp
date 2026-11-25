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
    // Sliding Window Min Cost
    // Learnt from Neatly Structured
    int n,k; cin>>n>>k;
    int a[n];
    for (int i=0; i<n; ++i){cin>>a[i];}
    // Initialise the following 
        // Initial Cost
        // Left Set -> n/2 + n%2
        // Rite Set -> n/2
        // Left Sum
        // Rite Sum
    oset<pair<int,int>> o;
    for (int i=0; i<k; ++i){o.insert({a[i],i});}
    int c=0;
    int med = (o.find_by_order((k/2 + k%2)-1))->first;
    oset<pair<int,int>> l;
    oset<pair<int,int>> r;
    int ls = 0;
    int rs = 0;
    int kc=0;
    for (auto x:o)
    {
        c+=abs(med - x.first);
        if (kc < (k/2+k%2)){l.insert({x.first,x.second}); ls+=x.first;}
        else               {r.insert({x.first,x.second}); rs+=x.first;}
        kc++;
    }
    cout << c << " ";

    // Now process for each window.
    for (int i=k; i<n; ++i)
    {
        pair<int,int> rem = {a[i-k],i-k};
        pair<int,int> ins = {a[i-0],i-0};

        if (l.find(rem) != l.end()){l.erase(rem); ls-=rem.first;}
        else {r.erase(rem); rs-=rem.first;}

        if (ins > *l.rbegin()){r.insert(ins); rs+=ins.first;}
        else{l.insert(ins); ls+=ins.first;}

        // After inserting and removing
        // I have to check for the sizes and equalise !

        if (l.size() > (k/2+k%2))
        {
            auto ext = *l.rbegin();
            l.erase(ext);
            ls-=ext.first;
            r.insert(ext);
            rs+=ext.first;
        }

        else if (r.size() > (k/2))
        {
            auto ext = *r.begin();
            r.erase(ext);
            rs-=ext.first;
            l.insert(ext);
            ls+=ext.first;
        }

        int ans = 0;
        int med = l.rbegin() -> first;
        ans += (l.size() * med) - ls;
        ans += rs - (r.size() * med);
        cout << ans << " ";
    }

    return 0;
}
