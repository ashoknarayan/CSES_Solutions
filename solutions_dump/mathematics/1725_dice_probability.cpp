#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define MOD 1000000007

int power(int base, int exp)
{
    int result = 1;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            result *= base;
        base *= base;
        exp /= 2;
    }
    return result;
}

signed main()
{
    int n; cin>>n;
    //int dp[n+1][6*n +1];
    vector<vector<double>> dp(n+1, vector<double> (6*n+1,0.0)); dp[0][0]=1.0;
                                    //!Notice that I converted everything to double
    for (int i=1; i<=n; ++i)
        for(int j=1; j<=6*n; ++j)
            for (int k=1; k<7; ++k)
                if (j-k >=0)
                    dp[i][j] += dp[i-1][j-k]*(1.0/6);
    int a,b; cin>>a>>b;
    double s = 0;
    for(int i=a; i<=b; ++i)
        s+=dp[n][i];
    cout << fixed << setprecision(6) << s << endl;
    return 0;
}

/*!
Dice Probability
This is clearly a DP Problem.
I will have to consider a n*6*n king of DP in this
Just update the number of ways in which you can produce the required sum and then add all the required answers

Had to learn the trick


*/



