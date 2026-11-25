#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<ll,ll>
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n,m,a,b,c; cin>>n>>m;
    vector<pii> g[n+1];
    while(m--) cin>>a>>b>>c, g[a].push_back({b,c});
    vector<ll> d(n+1,1e18), w(n+1), mn(n+1), mx(n+1);
    priority_queue<pii,vector<pii>,greater<>> q;
    d[1]=0; w[1]=1; q.push({0,1});
    while(q.size()) {
        auto [di,u]=q.top(); q.pop();
        if(di>d[u]) continue;
        for(auto &[v,c]:g[u]) {
            ll nd=di+c;
            if(d[v]>nd) {
                d[v]=nd; w[v]=w[u];
                mn[v]=mn[u]+1; mx[v]=mx[u]+1;
                q.push({d[v],v});
            } else if(d[v]==nd) {
                w[v]=(w[v]+w[u])%1000000007;
                mn[v]=min(mn[v],mn[u]+1);
                mx[v]=max(mx[v],mx[u]+1);
            }
        }
    }
    cout<<d[n]<<" "<<w[n]<<" "<<mn[n]<<" "<<mx[n];
}
