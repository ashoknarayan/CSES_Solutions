#include <bits/stdc++.h>
using namespace std;
using ll=long long; using dd=double;
#define sz(x) (ll)(x).size()
#define all(x) begin(x),end(x)
#define pb push_back
vector<array<ll,2>> trans(vector<ll>&a){
    vector<array<ll,2>>r;
    for(auto x:a){
        array<ll,2>c={x,1};
        while(sz(r)&&c[0]*r.back()[1]>=r.back()[0]*c[1])c[0]+=r.back()[0],c[1]+=r.back()[1],r.pop_back();
        r.pb(c);
    }return r;
}
tuple<dd,ll,ll> calc(vector<array<ll,2>>a,vector<array<ll,2>>b){
    ll p1=1,p2=1,s=a[0][0]+b[0][0],c1=a[0][1],c2=b[0][1];
    for(;p1<sz(a)&&s*(c1+c2+a[p1][1])<=(s+a[p1][0])*(c1+c2);p1++)s+=a[p1][0],c1+=a[p1][1];
    for(;p2<sz(b)&&s*(c1+c2+b[p2][1])<=(s+b[p2][0])*(c1+c2);p2++)s+=b[p2][0],c2+=b[p2][1];
    return {s/dd(c1+c2),c1,c2};
}
void solve(){
    ll n;cin>>n;vector<ll>a(n),b(n);for(auto&i:a)cin>>i;for(auto&i:b)cin>>i;
    auto ca=trans(a),cb=trans(b);
    auto r=max({calc(ca,cb),calc(ca,{{b[0],1}}),calc({{a[0],1}},cb)});
    cout<<get<1>(r)<<" "<<get<2>(r)<<"\n";
}
int main(){ios::sync_with_stdio(0);cin.tie(0);solve();}
