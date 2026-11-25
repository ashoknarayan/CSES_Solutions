#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

// Tree Matching
// DP in Tree
// dp[u,0] = max matching without taking u
// dp[u,1] = max matching with    taking u
// Declaring global var since I need to make a rec function
int dp[200001][2];
vector<int> g[200001];

void solve(int src, int par)
{
    vector<int> pre,suf;
    dp[src][0]=dp[src][1]=0; // Learnt this new way
    bool leaf = 1;
    for (int c:g[src])
        if (c!=par)
            leaf=0, solve(c,src);
    if (leaf) return;
    // Now you have reached the currently last unsolved node
    for(int c:g[src])
        if (c!=par)
        {
            int x = max(dp[c][0], dp[c][1]);
            pre.push_back(x); suf.push_back(x);
        }
    for (int i=1; i<pre.size(); ++i)
        pre[i]+=pre[i-1];
    for (int i=suf.size()-2; i>=0; --i)
        suf[i]+=suf[i+1];
    dp[src][0] = suf[0];
    int c_no = 0;
    for(int c : g[src])
    {
        if(c == par)continue;

        int lC = (c_no == 0) ? 0 : pre[c_no - 1];
        int rC = (c_no == (int)suf.size() - 1) ? 0 : suf[c_no + 1];

        dp[src][1] = max(dp[src][1], 1 + lC + rC + dp[c][0]);
        c_no++;
    }

}

signed main()
{
    int n;cin>>n;
    int a,b;
    for (int i=1; i<n; ++i)
    {
        cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    solve(1,0);
    cout << max(dp[1][0], dp[1][1]) << endl;

    return 0;
}
// I did not completely understand how this works. But this is a good start.


