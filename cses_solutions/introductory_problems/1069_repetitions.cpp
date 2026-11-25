#include <bits/stdc++.h>
using namespace std;
#define loop(i,a,b,s) for (int i=a; i!=b; i+=s)
#define endl "\n"
typedef long long ll;
const ll MOD = 1e9+7;
 
int main()
{
    string s; cin>>s;
    ll ans=1; ll tem=1;
    loop(i,1,s.size(),1)
    {
        if (s[i]==s[i-1]){tem++; ans=max(tem,ans);}
        else {tem=1;}
    }
    cout << ans << endl;
    return 0;
}
