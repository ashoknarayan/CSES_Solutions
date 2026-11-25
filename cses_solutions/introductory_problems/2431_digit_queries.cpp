#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define loop(i, a, b, s) for (ll i = a; i < b; i += s)
#define endl "\n"

void solve()
{
    ll k; cin>>k; 
    int p = 1;
    while (true)
    {
        ll cB = (p*9*pow(10,p-1));
        if (k>cB) {k -= cB;} 
        else{break;}
        p++;
    }

    ll b = pow(10,p-1);
    if (k%p!=0)
    {
        b+=(k/p); k%=p;
        string s = to_string(b);
        cout << s[k-1] << endl;
    }
    else
    {
        b+=(k/p)-1;
        string s = to_string(b);
        cout << s[p-1] << endl;
    }
    return;
}

int main() 
{
    int tc; cin>>tc;
    while(tc--){solve();cout << endl;}
    return 0;
}
