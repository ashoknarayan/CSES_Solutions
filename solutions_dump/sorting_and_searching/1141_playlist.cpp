#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

signed main()
{
    int n; cin>>n;
    int a[n]; 
    for(int i=0; i<n; ++i)
    {
        cin>>a[i];
    }

    int l=0;
    int ans=0;

    set<int> s; // NOT unordered_set <int> -> since it does not work

    for (int r=0; r<n; ++r)
    {
        if (s.find(a[r])==s.end())
        {
            s.insert(a[r]);
        }
        else
        {
           while (true)
           {
              if (a[l]==a[r]){l++; break;}
              else{s.erase(a[l]); l++;}
           }
        }
        ans = max(ans,r-l+1);
    }

    cout << ans << endl;
    return 0;
}
