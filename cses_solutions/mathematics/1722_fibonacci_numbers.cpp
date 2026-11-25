#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define MOD 1000000007


signed main()
{
    //~~//
    int n; cin>>n;
    int b[2][2]={{0,1},{1,1}}; // Base
    int r[2][2]={{1,0},{0,1}}; // Result
    if (n==0 || n==1){cout << n << endl; return 0;}
    n--;
    while(n>0)
    {
        if (n%2==1) // result = result * base;
        {
            int d[2][2]={{0,0},{0,0}};
            for (int i=0; i<2; ++i)
                for (int j=0; j<2; ++j)
                    for (int k=0; k<2; ++k)
                        d[i][j] = (d[i][j]+r[i][k]*b[k][j])%MOD;
            for (int i=0; i<2; ++i)
                for (int j=0; j<2; ++j)
                    r[i][j] = d[i][j];
        }

        int bb[2][2]={{0,0},{0,0}}; // base=base*base;
        for (int i=0; i<2; ++i)
            for (int j=0; j<2; ++j)
                for (int k=0; k<2; ++k)
                    bb[i][j] = (bb[i][j]+b[i][k]*b[k][j])%MOD;
        // Make a=b;
        for (int i=0; i<2; ++i)
            for (int j=0; j<2; ++j)
                b[i][j] = bb[i][j];


        n/=2;
    }
    cout << r[1][1] << endl;
    return 0;
}

/*!
    Finally learnt the matrix exponentiation of Fibonacci !

*/







