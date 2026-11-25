#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n,m,k; cin>>n>>m>>k;
    vector<vector<pair<int,int>>> g(n+1);
    int a,b,c;
    for(int i=0; i<m; ++i){
        cin>>a>>b>>c;
        g[a].push_back({c,b}); //{dist, node} -> different than earlier
    }

    vector<priority_queue<int>> ans(n+1);
    ans[1].push(0);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0,1}); // {dist, node}

    int pd, pn, cd, cn, tmp;
    while(!pq.empty()){
        pd = pq.top().first;
        pn = pq.top().second;
        pq.pop();
        if (pd > ans[pn].top()) continue;
        for (pair<int,int> cc : g[pn]){
            cd = cc.first;
            cn = cc.second;
            tmp = pd + cd;
            if (ans[cn].size() < k){
                ans[cn].push(tmp);
                pq.push({tmp,cn});
            }
            else if (ans[cn].size()==k && tmp<ans[cn].top()){
                ans[cn].pop();
                ans[cn].push(tmp);
                pq.push({tmp, cn});
            }
        }
    }
    vector<int> out;
    while(!ans[n].empty()){out.push_back(ans[n].top()); ans[n].pop();}
    for(int i=k-1; i>=0; --i) cout << out[i] << ' '; cout << endl;
    return 0;
}
