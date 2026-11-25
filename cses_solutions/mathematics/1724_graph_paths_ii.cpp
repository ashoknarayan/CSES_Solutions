#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define MOD 1000000007

signed main()
{
    int n,m,K;
    cin>>n>>m>>K; // Capital K since I am using k in the matrix multiplication
    vector<vector<int>> g(n+1,vector<int>(n+1,LLONG_MAX));
    vector<vector<int>> r(n+1,vector<int>(n+1,LLONG_MAX));
    int a,b,w;
    for (int i=0; i<m; ++i)
    {
        cin>>a>>b>>w;
        g[a][b] = min(g[a][b],w); // Same path can be inputted multiple times
        r[a][b] = min(r[a][b],w);
    }

    //for(int i=1; i<=n; ++i) r[i][i]=1;
    //! Now the matric exponentiation !
    K--; // Since I initialised r with g
    while(K>0)
    {
        if (K%2==1) // result = result * base;
        {
            //int d[2][2]={{0,0},{0,0}};
            vector<vector<int>> d(n+1,vector<int>(n+1,LLONG_MAX));
            for (int i=1; i<=n; ++i)
                for (int j=1; j<=n; ++j)
                    for (int k=1; k<=n; ++k)
                        if (g[i][k]!=LLONG_MAX && r[k][j]!=LLONG_MAX)
                            d[i][j] = min(d[i][j], (g[i][k]+r[k][j]));//d[i][j] = (d[i][j]+g[i][k]*r[k][j])%MOD;
            for (int i=1; i<=n; ++i)
                for (int j=1; j<=n; ++j)
                    r[i][j] = d[i][j];
        }

        //int bb[2][2]={{0,0},{0,0}}; // base=base*base;
        vector<vector<int>> bb(n+1,vector<int>(n+1,LLONG_MAX));
        for (int i=1; i<=n; ++i)
            for (int j=1; j<=n; ++j)
                for (int k=1; k<=n; ++k)
                    if (g[i][k]!=LLONG_MAX && g[k][j]!=LLONG_MAX)
                        bb[i][j] = min(bb[i][j], (g[i][k]+g[k][j]));//bb[i][j] = (bb[i][j]+g[i][k]*g[k][j])%MOD;
        // Make a=b;
        for (int i=1; i<=n; ++i)
                for (int j=1; j<=n; ++j)
                g[i][j] = bb[i][j];


        K/=2;
    }
    if (r[1][n]==LLONG_MAX){cout << -1 << endl;}
    else cout << r[1][n] << endl;
    return 0;
}

/*!
I understood most of the problem,
But I have no idea on why it is r[1][n]-1 instead of r[1][n]
I just put -1 simply since it gave 28 on the example test.
And it got ACCEPTED.
So I am going to leave it jsut like that !

Found it. It is because initialising r with identit

I have initialised with graph initially and did k--.
I believe this must work lets see

It worked. Now there is no need of -1 !!!
Excellent da ashok. I am very proud of myself
I have understood it perfectly ..
Here instead of repeated multiplication we are using the same method but not muliplying,
we are storing the min of all paths in all runs . therefore, no point in putting r as Identity matrix
putting it a 0 matrix will make us to cover some edge cases. but initialising as g only and cutting down round 1 is the best method
*/
