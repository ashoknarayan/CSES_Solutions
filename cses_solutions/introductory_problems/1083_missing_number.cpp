#include <bits/stdc++.h>
using namespace std;
#define loop(i,a,b,s) for (int i=a; i!=b; i+=s)
#define endl "\n"
typedef long long ll;
const ll MOD = 1e9+7;
 
int main()
{
    ll n; cin>>n;
    ll s=0;
    loop(i,1,n,1){int elm; cin>>elm; s+=elm;}
    cout << (((n)*(n+1)/2)-s) << endl;
    return 0;
}
