#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
#define loop(i,a,b,s) for (ll i=a; i<b; i+=s)
#define pool(i,a,b,s) for (ll i=a; i>b; i-=s)
#define endl "\n"
const ll MOD = 1e9+7;
 
int main()
{
    ll n; cin>>n;
    int c = n%4;
    if (c==1 || c==2){cout << "NO";}
    else
    {
        cout << "YES" << endl;
        ll need = (n)*(n+1)/4;
        ll br; ll m; int ad=0; int bd=0;
        pool(i,n,0,1)
        {
            if (need>i){ad++;need-=i;}
            else {br=need;m=i;ad++;break;}
        }
        loop(j,1,m+1,1)
        {
            if (j!=br){bd++;}
        }
        need = (n)*(n+1)/4;
        cout << ad << endl;
        pool(i,n,0,1)
        {
            if (need>i){cout << i << " ";need-=i;}
            else {br=need;m=i;cout << br << endl;break;}
        }
        cout << bd << endl;
        loop(j,1,m+1,1)
        {
            if (j!=br){cout << j << " ";}
        }
    }
    return 0;
}
