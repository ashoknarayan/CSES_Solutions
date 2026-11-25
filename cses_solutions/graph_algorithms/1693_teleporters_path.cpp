#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define endl '\n'

int n,m; 
vector<int> g[100001];
vector<int> ind(100001,0);
vector<int> otd(100001,0);

bool check_Euler()
{
    int sV=0; int eV=0;
    for(int i=1; i<=n; ++i)
    {
        int d = ind[i]-otd[i];
        if (d==-1) sV++;
        else if (d==1) eV++;
        else if (d!=0) return false;
    }

    return (sV==1 && eV==1 && ind[1]==otd[1]-1); // Very important conditions
}

void Euler_Path(int s)
{

    stack<int> path;
    vector<int> result;
    path.push(s);
    while(!path.empty())
    {
        int u=path.top();
        if (otd[u]>0)
        {
            int v=g[u].back();
            g[u].pop_back(); // Just note
            otd[u]--;
            ind[v]--;
            path.push(v);
        }
        else
        {
            result.push_back(u);
            path.pop();
        }
    }
    if (result.size()!=m+1 || result[0]!=n) {cout << "IMPOSSIBLE" << endl; exit(0);}
    for(int i=result.size()-1; i>=0; --i)
        cout << result[i] << " ";
    return;
}

signed main()
{
    cin>>n>>m;
    int a,b; 
    for(int i=0; i<m; ++i)
    {
        cin>>a>>b;
        g[a].push_back(b);
        ind[b]++;
        otd[a]++;
    }
    if (!check_Euler()) cout << "IMPOSSIBLE" << endl;
    else
    {
        Euler_Path(1);
    }
    return 0;
}
 
/*
Eulers Path = Path that covers all edges exactly once
I am not very clear with the algorithm but will cover it by watching some animation
This is enough for now 
*/
