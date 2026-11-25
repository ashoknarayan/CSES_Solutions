#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<array<int,3>> edges; // {s,e,w}
int n;
vector<int>  d(100001,-1e18);
vector<int>  g[100001]; // reverse graph
vector<bool> v(100001, false); // tells if a pt can be reached from last

void nreach(){
    queue<int> q; 
    q.push(n);
    v[n] = true;
    while(q.size()){
        int par = q.front(); q.pop();
        for (int chi : g[par])
            if (!v[chi])
                v[chi] = true, q.push(chi);
    }
}

void bell(){
    d[1] = 0;
    for(int i=0; i<=n; ++i)
        for (auto x:edges)
            if (d[x[0]] != -1e18)
                if (d[x[1]] < d[x[0]]+x[2])
                    d[x[1]] = d[x[0]]+x[2];          
}

bool cycle(){
    nreach();
    for (auto x:edges)
        if (d[x[0]] != -1e18)
            if (d[x[1]] < d[x[0]]+x[2])
                if (v[x[1]])
                    return true; 
    return false;
}


signed main() {
    int m; cin>>n>>m;
    array<int,3> x;
    for(int i=0; i<m; ++i){
        cin>>x[0]>>x[1]>>x[2];
        edges.push_back(x);
        g[x[1]].push_back(x[0]);
    }
    bell();
    if (cycle()) cout << -1 << endl;
    else cout << d[n] << endl;
    return 0;
}
