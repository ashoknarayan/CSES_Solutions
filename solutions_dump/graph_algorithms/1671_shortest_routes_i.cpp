#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    int n,m; cin>>n>>m;
    vector<vector<pair<int,int>>> g(n+1);
    int a,b,c;
    for(int i=0; i<m; ++i){
        cin>>a>>b>>c;
        g[a].push_back({b,c});
    }
    // Do the dijkstraa 
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<long long> dist(n+1,LLONG_MAX);
    dist[1] = 0;
    pq.push({0,1});

    while(!pq.empty()){
        pair<int,int> par = pq.top(); // {dist,node}
        pq.pop();
        if (par.first > dist[par.second]) continue;
        for(pair<int,int> c : g[par.second]){ // {node, dist}
            if(dist[c.first] > dist[par.second] + c.second){
                dist[c.first] = dist[par.second] + c.second;
                pq.push({dist[c.first], c.first});
            }
        }
    }

    for(int i=1; i<=n; ++i) cout << dist[i] << ' ';
        cout << endl;
    return 0;
}
