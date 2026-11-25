#include <bits/stdc++.h>
using namespace std;
#define loop(i,a,b,s) for (int i=a; i!=b; i+=s)
#define endl "\n"
typedef long long ll;
const ll MOD = 1e9+7;

int main()
{
    ll n; cin>>n;
    ll a[n]; loop(i,0,n,1){cin>>a[i];}
    ll m=a[0]; ll ans=0;
    for(auto x:a)
    {
        if (x>m){m=x;}
        else{ans+=m-x;}
    }
    cout << ans << endl;
    return 0;
}
