#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using oset =tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
void solve();
#define endl "\n"
#define int  long long
#define fio ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
signed main()
{
    fio;
    int n; cin>>n; int r=1;
    map<int,int> m;
    for (int i=0; i<n; ++i)
    {
        int a,b; cin>>a>>b;
        if (m.find(b) != m.end()){m[b]=max(m[b],a);}
        else {m[b]=a;}

    }
    auto lk = m.begin();
    for (auto i=m.begin(); i!=m.end(); ++i)
    {
        if (i->second >= lk->first){lk = i;r++;}
    }
    cout << r << endl;
    return 0;
}

