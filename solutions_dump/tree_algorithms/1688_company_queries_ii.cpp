#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,a,b) for (int i=a; i<=b; ++i)
#define per(i,b,a) for (int i=b; i>=a; --i)
#define fi ios_base::sync_with_stdio(false);cin.tie(NULL)
#define endl '\n'

int p[200001];
int u[200001][21];
int d[200001];


int LCA(int a, int b)
{
    if (d[a]<d[b]) swap(a,b);
    int t=d[a]-d[b];
    per(i,20,0)
        if(t&(1<<i))
            a=u[a][i];
    if (a==b) return a;
    per(i,20,0)
        if (u[a][i]!=u[b][i])
            a=u[a][i] , b=u[b][i];
    return u[a][0];
}

int main(/*~*/)
{
    fi;
    int n,q;
    cin>>n>>q; p[1]=0; d[0]=-1;
    rep(i,2,n) cin>>p[i];
    rep(v,1,n)
    {
        u[v][0] = p[v];
        d[v]=d[p[v]]+1; // This will take care of distance.
        rep(j,1,20) u[v][j] = u[u[v][j-1]][j-1];
    }
    int a,b;
    while (q--)
    {
        cin>>a>>b;
        cout << (LCA(a,b)) << endl;
    }
    return 0;
}
