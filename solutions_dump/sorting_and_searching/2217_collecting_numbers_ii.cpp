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
    int m; cin>>m;
 
    int a[n+1]; 
    for(int i=1; i<=n; ++i){cin>>a[i];}
 
    int b[n+1];
    for(int i=1; i<=n; ++i){b[a[i]]=i;}
 
    int t=1;
    for (int i=1; i< n; ++i){if (b[i]>b[i+1]){t++;}}
 
    //cout << t << endl;
    for (int i=0; i<m; ++i)
    {
        int x,y; cin>>x>>y;
        int xx = a[x];
        int yy = a[y];
        if (xx>yy){swap(xx,yy);}
        // Have fixed xx<yy for clarity.
 
        if(yy-xx==1)
        {
            if (b[xx]>b[yy]){t--;}
            else {t++;}
 
            // Now the sides
            if (b[xx-1]>b[xx] && b[xx-1]<b[yy] && xx>1){t--;}
            if (b[xx-1]<b[xx] && b[xx-1]>b[yy] && xx>1){t++;}
            if (b[yy+1]<b[yy] && b[yy+1]>b[xx] && yy<n){t--;}
            if (b[yy+1]>b[yy] && b[yy+1]<b[xx] && yy<n){t++;}
        }
        else
        {
            // Cover all cases
            //Before Swap
 
            if (b[xx]>b[xx+1] && xx<n){t--;}
            if (b[xx]<b[xx-1] && xx>1){t--;}
            if (b[yy]>b[yy+1] && yy<n){t--;}
            if (b[yy]<b[yy-1] && yy>1){t--;}
 
            //After  Swap
            if (b[yy]>b[xx+1] && xx<n){t++;}
            if (b[yy]<b[xx-1] && xx>1){t++;}
            if (b[xx]>b[yy+1] && yy<n){t++;}
            if (b[xx]<b[yy-1] && yy>1){t++;}
        }
 
        swap(a[x ],a[y ]);
        swap(b[xx],b[yy]);
 
        cout << t << endl;
    }
    return 0;
}
