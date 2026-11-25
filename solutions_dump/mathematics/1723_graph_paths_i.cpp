#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define MOD 1000000007

signed main()
{
    int n,m,K;
    cin>>n>>m>>K; // Capital K since I am using k in the matrix multiplication
    vector<vector<int>> g(n+1,vector<int>(n+1,0));
    int a,b;
    for (int i=0; i<m; ++i)
    {
        cin>>a>>b;
        g[a][b]++; // Same path can be inputted multiple times

    }
    vector<vector<int>> r(n+1,vector<int>(n+1,0));
    for(int i=1; i<=n; ++i) r[i][i]=1;
    //! Now the matric exponentiation !
    while(K>0)
    {
        if (K%2==1) // result = result * base;
        {
            //int d[2][2]={{0,0},{0,0}};
            vector<vector<int>> d(n+1,vector<int>(n+1,0));
            for (int i=1; i<=n; ++i)
                for (int j=1; j<=n; ++j)
                    for (int k=1; k<=n; ++k)
                        d[i][j] = (d[i][j]+g[i][k]*r[k][j])%MOD;
            for (int i=1; i<=n; ++i)
                for (int j=1; j<=n; ++j)
                    r[i][j] = d[i][j];
        }

        //int bb[2][2]={{0,0},{0,0}}; // base=base*base;
        vector<vector<int>> bb(n+1,vector<int>(n+1,0));
        for (int i=1; i<=n; ++i)
            for (int j=1; j<=n; ++j)
                for (int k=1; k<=n; ++k)
                    bb[i][j] = (bb[i][j]+g[i][k]*g[k][j])%MOD;
        // Make a=b;
        for (int i=1; i<=n; ++i)
                for (int j=1; j<=n; ++j)
                g[i][j] = bb[i][j];


        K/=2;
    }
    cout << r[1][n] << endl;
    return 0;
}

/*!
The matter
*/
