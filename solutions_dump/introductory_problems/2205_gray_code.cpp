#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
#define loop(i,a,b,s) for (ll i=a; i<b; i+=s)
#define pool(i,a,b,s) for (ll i=a; i>b; i-=s)
#define endl "\n"
const ll MOD = 1e9+7;

vector<string> grey(int n)
{
    if (n==1){return {"0","1"};}
    vector<string> a; vector<string> b;
    for (auto x:grey(n-1)){a.push_back(x+"0");}
    for (auto x:grey(n-1)){b.push_back(x+"1");}
    reverse(b.begin(),b.end());
    for (auto x:b){a.push_back(x);}
    return a;
}

int main()
{
    int n; cin>>n;
    for (auto x:grey(n)){cout << x << endl;}
    return 0;
}
