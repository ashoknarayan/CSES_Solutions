#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,a,b) for (int i=a; i<=b; ++i)
#define fi ios_base::sync_with_stdio(false);cin.tie(NULL)
#define endl '\n'

int p[200001];
int u[200001][21];
int d[200001];


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
    int node,step;
    while (q--)
    {
         cin>>node>>step;
         rep(j,0,20)
            if (step&(1<<j))
                node=u[node][j];
         cout << (node==0 ? -1:node) << endl;
    }
    return 0;
}


/*!
Tree Ancestors [Binary Lifting]
If A above B, then A<B in value
so 1 has no boss

The edge case handling is top notch !
Also learnt what is fi.
Distance is also calculated. No need of DFS as far as now
*/
