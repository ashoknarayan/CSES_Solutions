#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


signed main()
{
    int n; cin>>n;
    int a[n];
    for (int i=0; i<n; ++i){cin>>a[i];}

    int t=INT_MIN;
    int b=INT_MIN;

    for (auto x:a)
    {
        t = max(x,x+t);
        b = max(b,t);
    }

    cout  << b << endl;
    return 0;
}
