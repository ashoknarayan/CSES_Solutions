#include <bits/stdc++.h>
using namespace std;

int main(){
    int a,b; cin>>a>>b;
    vector<vector<int>> dp((a+1), vector<int>((b+1), (a+b)));
    { // Base case
        for (int i=0; i<=a; ++i) dp[i][0]=0;
        for (int j=0; j<=b; ++j) dp[0][j]=0;
        for (int k=0; k<=min(a,b); ++k) dp[k][k]=0;
    }
    for (int i=1; i<=a; ++i){
        for (int j=1; j<=b; ++j){

            for(int ii=1; ii<=i; ++ii){
                dp[i][j] = min(dp[i][j], dp[i-ii][j]+dp[ii][j]+1);
            }
            for(int jj=1; jj<=j; ++jj){
                dp[i][j] = min(dp[i][j], dp[i][j-jj]+dp[i][jj]+1);
            }
        }
    }

    cout << dp[a][b] << endl;
    return 0;
}
