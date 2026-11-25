#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using oset =tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update> ;
#define endl "\n"
#define int  long long
#define fio ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

signed main()
{
    int n; cin>>n;
    oset<pair<int,int>> a,b;
    vector<array<int,3>> c(n);
    int aa[n];
    int bb[n];

    for (int i=0; i<n; ++i)
    {
        cin >> c[i][0] >> c[i][1];
        c[i][2] = i;
    }

    // Sorting according to my need as explained
    sort(c.begin(),c.end(), [&](const array<int,3>i, const array<int,3>j)
    {
        return ((i[0]<j[0]) || (i[0]==j[0] && i[1]>j[1]));
    });

    // Part 1 of the question
    // How many ranges does it contain

    for (int i=0; i<n; ++i)
    {
        int j = n-(i+1);
        aa[c[j][2]] = a.order_of_key({c[j][1]+1 , -1});
        a.insert({c[j][1],i});
    }

    // Part 2 of the question
    // How many ranges do contain it 

    for (int i=0; i<n; ++i)
    {
        bb[c[i][2]] = i - b.order_of_key({c[i][1] , -1});
        b.insert({c[i][1],i});
    }

    // Output the answers

    for (auto x:aa){cout << x << " ";}
        cout << endl;
    for (auto x:bb){cout << x << " ";}


}
