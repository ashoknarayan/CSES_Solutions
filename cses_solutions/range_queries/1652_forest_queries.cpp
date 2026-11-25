#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

// Forest Queries
// Got the Idea when I was about to sleep. So came to code!
signed main()
{
    // Storing in a nice way !
    int n,q; cin>>n>>q;
    vector<vector<int>> f(n+1, vector<int>(n+1,0));
    char e; // i th row, j th column
    for (int i=1; i<=n;++i)
    {
        for (int j=1; j<=n; ++j)
        {
            cin>>e;
            int t=(f[i][j-1]+f[i-1][j]) - f[i-1][j-1];
            f[i][j] = (e=='*'? t+1:t);
        }
    }
    int y1,y2,x1,x2;
    int y,Y,x,X; // These are for my calculations
    while(q--)
    {
        cin>>y1>>x1>>y2>>x2;
        y = min(y1,y2)-1; Y=max(y1,y2);
        x = min(x1,x2)-1; X=max(x1,x2);
        cout << (f[Y][X]+f[y][x])-(f[Y][x]+f[y][X]) << endl;
    }
    return 0;
}

