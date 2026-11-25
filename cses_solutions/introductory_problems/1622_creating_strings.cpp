#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
#define loop(i,a,b,s) for (ll i=a; i<b; i+=s)
#define pool(i,a,b,s) for (ll i=a; i>b; i-=s)
#define endl "\n"
const ll MOD = 1e9+7;
 
int main() 
{
    string s; cin>>s; sort(s.begin(),s.end());
    ll c=0;
    do{c++;}
    while (next_permutation(s.begin(),s.end()));
    cout << c << endl;
    do{cout << s << endl;}
    while (next_permutation(s.begin(),s.end()));
    return 0;
}
