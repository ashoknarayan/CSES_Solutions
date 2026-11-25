#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
#define loop(i,a,b,s) for (ll i=a; i<b; i+=s)
#define endl "\n"
const ll MOD = 1e9+7;

int main()
{
    ll n; cin>>n;
    ll ans=0;
    while(n>4)
    {
        ans+=(n/5);
        n/=5;
    }
    cout << ans << endl;
    return 0;
}
