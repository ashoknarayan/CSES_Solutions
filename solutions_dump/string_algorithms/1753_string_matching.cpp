#include <bits/stdc++.h>
using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~~~//
void solve(); int main(){int tc=1;
        //cin>>tc;
while(tc--) solve(); return 0;}
//~~~~~~~~~~~~~~~~~~~~~~~~~~//

void solve()
{
    //! Revise KMP
    string s,p; cin>>s>>p;
    s = p+"X"+s;
    int n=s.size();
    int pre[n];
    int l=0;
    int i=1;
    pre[0]=0;
    while(i<n)
    {
        if (s[i]==s[l])
        {
            ++l;
            pre[i]=l;
            ++i;
            continue;
        }

        if (l==0) pre[i]=0, ++i;
        else l = pre[l-1];
    }
    int c=0;
    for(int i:pre) if (i==p.size()) ++c;
    cout << c << endl;
    return;
}

