#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
#define loop(i,a,b,s) for (ll i=a; i<b; i+=s)
#define pool(i,a,b,s) for (ll i=a; i>b; i-=s)
#define endl "\n"
const ll MOD = 1e9+7;
 
int main()
{
    int tc; cin>>tc;
    while (tc--)
    {
        ll a; cin>>a; ll b; cin>>b;
        if (max(a,b)>2*min(a,b)){cout << "NO" << endl;}
        else 
        {
            if ((a+b)%3==0){cout << "YES" << endl;}
            else {cout << "NO" << endl;}
        }
    }
    return 0;
}

