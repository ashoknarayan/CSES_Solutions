#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    int n,m,q; cin>>n>>m>>q;
    vector<vector<pair<int,int>>> g(n+1);
    int a,b,c;
    vector<vector<int>> ans(n+1, vector<int>(n+1, LLONG_MAX));
    for (int i=1; i<=n; ++i){ans[i][i] = 0;}
    for(int i=0; i<m; ++i){
        cin>>a>>b>>c;
        ans[a][b] = ans[b][a] = min(ans[a][b], c);
    }
    // Do the FW 
    for (int k=1; k<=n; ++k)
        for (int i=1; i<=n; ++i)
            for (int j=1; j<=n; ++j)
                if (ans[i][k]!=LLONG_MAX && ans[k][j]!=LLONG_MAX)
                    ans[i][j] = min(ans[i][j], ans[i][k]+ans[k][j]);
    
    while(q--){
        cin>>a>>b;
        cout << (ans[a][b] == LLONG_MAX ? -1 : ans[a][b]) << endl;
    }
    return 0;
}
