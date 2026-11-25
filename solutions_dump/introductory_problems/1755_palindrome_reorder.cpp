#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

signed main()
{
    string in; cin>>in;
    vector<int> a(26,0);
    for (int i:in)
        a[i-'A']++;
    int c=0;
    int ind=-1; // Check why
    for (int i=0; i<26; ++i)
    {
        if (a[i]%2==1)
        {
            if (c==1)
            {
                cout << "NO SOLUTION" << endl;
                return 0;
            }
            else
            {
                c++;
                ind=i;
            }
        }
    }
    char oc;
    if (ind!=-1) oc = 'A'+ind;
    string s="";
    for (int i=0; i<26; ++i)
        for(int j=0; j<a[i]/2; ++j)
            s+=('A'+i);
    string ans=s;
    if (ind!=-1) ans+=oc;
    reverse(s.begin(),s.end());
    ans+=s;
    cout << ans << endl;

    return 0;
}
