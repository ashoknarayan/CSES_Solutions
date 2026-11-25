#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
 
 
signed main()
{
    int n; cin>>n;
    int a[n];
    for (int i=0; i<n; ++i){cin>>a[i];}
    sort(a,a+n);
    int m = a[n/2];
    int an=0;
    for (auto x:a){an += abs(x-m);}
    cout << an << endl;
    return 0;
}
