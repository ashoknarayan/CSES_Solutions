#include <bits/stdc++.h>
using namespace std;
#define int long long
 
signed main()
{
    int n,x; cin>>n>>x;
    int a[n];
    for (int i=0; i<n; ++i){cin>>a[i];}
    sort(a,a+n);
    
    int l=0;
    int r=n-1;
    int g=0;

    while (l<=r)
    {
        if ((a[l]+a[r])<=x){l++;}
        r--;
        g++;
    }

    cout << g << endl;
}
