#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
#define loop(i,a,b,s) for (ll i=a; i<b; i+=s)
#define endl "\n"
const ll MOD = 1e9+7;

int main()
{
    ll i ;cin>>i;
    loop(k,1,i+1,1)
    {
        ll d=4*(k-2)*(k-1);
        ll t=(k*k)*((k*k)-1)/2;
        cout << t-d << endl;
    }
    return 0;
}
