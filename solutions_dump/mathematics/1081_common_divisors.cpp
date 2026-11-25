#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

signed main()
{
    int maxn = 1e6+1;
    vector<int> freq(maxn,0);
    int n; cin>>n;
    int e;
    for(int i=0; i<n; ++i)
    {
        cin>>e;
        freq[e]++;
    }

    vector<int> mult(maxn,0);
    int ans=0;
    for (int i=1; i<maxn; ++i)
    {
        for(int j=i; j<maxn; j+=i)
        {
            mult[i]+=freq[j];
            if (mult[i]>=2)
                ans=i; // ans=max(ans,i);
        }
    }
    cout << ans << endl;
}
