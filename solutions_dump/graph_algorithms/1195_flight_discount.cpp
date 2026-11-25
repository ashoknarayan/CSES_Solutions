#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
 
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n, m; cin>>n>>m;
    int k=1; // cin >> k;
    vector<vector<pair<int,int>>> g(n+1);
    int a,b,c; 
    for(int i=0; i<m; ++i){
        cin>>a>>b>>c;
        g[a].push_back({b,c});
    }
    // Implement the big dijkstraa
    priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> pq;
    // {weight, node, rem_coupon}
    vector<vector<int>> ans(n+1, vector<int> (k+1, LLONG_MAX));
    pq.push({0,1,k});
    for (int i=1; i<=k; ++i) ans[1][i] = 0;
    while(pq.size()){
        array<int,3> pp = pq.top();
        int wtt = pp[0];
        int par = pp[1];
        int rem = pp[2];
        pq.pop();
 
        if (wtt > ans[par][rem]) continue;
 
        for(pair<int,int> child : g[par]){
            int son = child.first;
            int dst = child.second;
            if (ans[son][rem] > wtt + dst){
                ans[son][rem] = wtt+dst;
                pq.push({ans[son][rem], son, rem});
            }
            if (rem > 0){
                if (ans[son][rem-1] > wtt + dst/2){
                    ans[son][rem-1] = wtt + dst/2;
                    pq.push({ans[son][rem-1], son, rem-1});
                }
            }
        }
    }
    cout << ans[n][0] << endl;
    return 0;
}
