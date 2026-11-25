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
    
    int s=0;
    for (auto x:a)
    {
        if (s+1>=x){s+=x;}
        else{break;}
    }

    cout << s+1 << endl;
    return 0;
}
