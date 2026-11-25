#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define int long long
#define endl '\n'

template <typename T>
using seto = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Collecting Numbers II



signed main()
{
    int n; cin>>n;

    int a[n+1];
    for (int i=1; i<=n; ++i){cin>>a[i];}

    int b[n+1];
    for (int i=1; i<=n; ++i){b[a[i]]=i;}

    int t=1;
    for (int i=1; i< n; ++i){if (b[i]>b[i+1]){t++;}}

    cout << t << endl;
}

// This is the plan
