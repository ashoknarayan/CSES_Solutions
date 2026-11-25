#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
#define loop(i,a,b,s) for (ll i=a; i<b; i+=s)
#define pool(i,a,b,s) for (ll i=a; i>b; i-=s)
#define endl "\n"
const ll MOD = 1e9+7;

void TOH(ll n, int a, int b, int c)
{
    if (n==1){cout<<a<<" "<<c<< endl;return;}
    TOH(n-1,a,c,b);
    cout << a << " " << c << endl;
    TOH(n-1,b,a,c);
}

int main()
{
    ll n; cin>>n;
    cout << pow(2,n)-1 << endl;
    TOH(n,1,2,3);    
    return 0;
}
