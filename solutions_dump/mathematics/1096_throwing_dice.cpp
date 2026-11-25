#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define MOD 1000000007


signed main()
{
    //~~//
    int n; cin>>n;
    //int b[2][2]={{0,1},{1,1}}; // Base
    int b[6][6] =
    {
        {0,1,0,0,0,0},
        {0,0,1,0,0,0},
        {0,0,0,1,0,0},
        {0,0,0,0,1,0},
        {0,0,0,0,0,1},
        {1,1,1,1,1,1}
    };
    //int r[2][2]={{1,0},{0,1}}; // Result
    int r[6][6] =
    {
        {1,0,0,0,0,0},
        {0,1,0,0,0,0},
        {0,0,1,0,0,0},
        {0,0,0,1,0,0},
        {0,0,0,0,1,0},
        {0,0,0,0,0,1}
    };
    if (n<=1){cout << n << endl; return 0;}

    while(n>0)
    {
        if (n%2==1) // result = result * base;
        {
            //int d[2][2]={{0,0},{0,0}};
            int d[6][6] =
            {
                {0,0,0,0,0,0},
                {0,0,0,0,0,0},
                {0,0,0,0,0,0},
                {0,0,0,0,0,0},
                {0,0,0,0,0,0},
                {0,0,0,0,0,0}
            };
            for (int i=0; i<6; ++i)
                for (int j=0; j<6; ++j)
                    for (int k=0; k<6; ++k)
                        d[i][j] = (d[i][j]+r[i][k]*b[k][j])%MOD;
            for (int i=0; i<6; ++i)
                for (int j=0; j<6; ++j)
                    r[i][j] = d[i][j];
        }

        //int bb[2][2]={{0,0},{0,0}}; // base=base*base;
        int bb[6][6] =
            {
                {0,0,0,0,0,0},
                {0,0,0,0,0,0},
                {0,0,0,0,0,0},
                {0,0,0,0,0,0},
                {0,0,0,0,0,0},
                {0,0,0,0,0,0}
            };
        for (int i=0; i<6; ++i)
            for (int j=0; j<6; ++j)
                for (int k=0; k<6; ++k)
                    bb[i][j] = (bb[i][j]+b[i][k]*b[k][j])%MOD;
        // Make a=b;
        for (int i=0; i<6; ++i)
            for (int j=0; j<6; ++j)
                b[i][j] = bb[i][j];


        n/=2;
    }
    cout << r[5][5] << endl;
    return 0;
}

/*!
Using the Fibonacci Code to solve the "Throuwing Dice"

Mahn!!! I am so proud of this !!!
I am really very happy
super da ashok !
*/
