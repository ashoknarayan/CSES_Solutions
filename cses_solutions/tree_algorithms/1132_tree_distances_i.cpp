// Trees -> Just for that CS dude ! 
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define mod 1000000007

int n;
vector<int> g[200001];
vector<int> d1(200001,0);
vector<int> d2(200001,0);

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

void bfsdist(int s, vector<int>& d)
{
    vector<bool> v(n+1,false);
    queue<int> q; v[s]=true; q.push(s);
    while(q.size())
    {
        s = q.front(); q.pop();
        for(int ss:g[s])
            if (!v[ss])
                v[ss]=true, d[ss]=d[s]+1, q.push(ss);
    }
}

signed main()
{
    cin>>n;
    int a,b;
    for(int i=1; i<n; ++i){
        cin>>a>>b; 
        g[a].push_back(b);
        g[b].push_back(a);}
    int s1 = bfsmx( 1).first;
    int s2 = bfsmx(s1).first;
    bfsdist(s1,d1);
    bfsdist(s2,d2);

    for(int i=1; i<=n; ++i)
        cout << max(d1[i],d2[i]) << " ";
    return 0;
}
