// Trees -> Just for that CS dude ! 
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define mod 1000000007
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
 
int n;
vector<int> g[200001];
 
pair<int,int> bfsmx(int dad)
{
    int x=0; int s=dad;
    vector<bool> v(n+1,false);
    queue<pair<int,int>> q; q.push({dad,x}); v[dad]=true;
    while(q.size())
    {
        x = q.front().second;
        s = q.front().first;
        q.pop();
        for (int ss:g[s])
        {
            if (!v[ss])
            {
                v[ss]=true;
                q.push({ss,x+1});
            }  
        }
        
    }
    return {s,x};
}
 
signed main()
{
    fast_io;
    cin>>n;
    int a,b;
    for(int i=1; i<n; ++i){
        cin>>a>>b; 
        g[a].push_back(b);
        g[b].push_back(a);}
    cout << bfsmx((bfsmx(1).first)).second << endl;
    return 0;
}
