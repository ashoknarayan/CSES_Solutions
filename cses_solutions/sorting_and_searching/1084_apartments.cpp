#include <bits/stdc++.h>
using namespace std;
#define int long long
 
signed main()
{
    int n,m,k; cin>>n>>m>>k;
    int a[n]; 
    for (int i=0; i<n; ++i){cin>>a[i];}
    sort(a,a+n);

    int b[m];
    for (int i=0; i<m; ++i){cin>>b[i];}
    sort(b,b+m);

    int ai=0;
    int bi=0;
    int an=0;

    while(ai<n && bi<m)
    {
        int t = abs(a[ai]-b[bi]);
        if (t<=k)
        {
            an++; ai++; bi++;
        }
        else
        {
            if(a[ai]>b[bi])
            {
                bi++;
            }
            else // a[ai]<=b[bi];
            {
                ai++;
            }
        }
    }
    cout << an << endl;
    return 0;
}
