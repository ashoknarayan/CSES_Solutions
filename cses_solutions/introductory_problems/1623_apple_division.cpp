#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
#define loop(i,a,b,s) for (ll i=a; i<b; i+=s)
#define pool(i,a,b,s) for (ll i=a; i>b; i-=s)
#define endl "\n"
const ll MOD = 1e9+7;

string bR(ll n)
{
    string s="";
    while (n>0){s+=(char)(n%2+'0');n/=2;}
    reverse(s.begin(),s.end());
    return s;
}

int main() 
{
    int n; cin>>n; int a[n]; ll m=INT_MAX;
    loop(i,0,n,1){cin>>a[i];}
    loop(i,0,pow(2,n)+1,1)
    {
        ll s=0;
        string b=bR(i);
        loop(j,0,n,1)
        {
            if (b[j]=='0'){s-=a[j];}
            else{s+=a[j];}
        }
        m = min(abs(s),m);
    }
    cout << m << endl;
    return 0;
}
