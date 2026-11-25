#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,a,b) for (int i=a; i<=b; ++i)
#define per(i,b,a) for (int i=b; i>=a; --i)
#define fi ios_base::sync_with_stdio(false);cin.tie(NULL)
#define endl '\n'

int p[200001];
vector<int> adj[200001];
int u[200001][21];
int d[200001];

void dfs(int v, int par)
{
    p[v] = par;
    u[v][0] = par;
    d[v] = d[par] + 1;
    for (int child : adj[v])
        if (child != par)
            dfs(child, v);
}


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
    int dad,son;
    rep(i,2,n) // Little change in getting input
    {
        cin>>dad>>son;
        adj[dad].push_back(son);
        adj[son].push_back(dad);
    }
    dfs(1,0);
    rep(j,1,20)
        rep(v,1,n)
            if (u[v][j-1]!=0)
                u[v][j] = u[u[v][j-1]][j-1];

    int a,b;
    while (q--)
    {
        cin>>a>>b;
        cout << d[a]+d[b]-2*d[LCA(a,b)] << endl;
    }
    return 0;
}

// Main error was you can not assume here that if a<b then a might be the boss of b
