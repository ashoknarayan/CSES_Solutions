#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
#define loop(i,a,b,s) for (ll i=a; i<b; i+=s)
#define pool(i,a,b,s) for (ll i=a; i>b; i-=s)
#define endl "\n"
const ll MOD = 1e9+7;

void solve()
{
    ll y,x; cin>>y>>x; ll ans;
    if (y>x)
    {
        ll b = ((y-y%2)*(y-y%2))+y%2;
        if (y%2==0){ans=b-x+1;}
        else{ans=b+x-1;}
    }
    else
    {
        ll b = ((x-1+x%2)*(x-1+x%2))+(1-x%2);
        if (x%2==0){ans = b+y-1;}
        else{ans = b-y+1;}
    }
    cout << ans << endl;
}
int main()
{
    int tc; cin>>tc;
    while(tc--){solve();}
    return 0;
}
