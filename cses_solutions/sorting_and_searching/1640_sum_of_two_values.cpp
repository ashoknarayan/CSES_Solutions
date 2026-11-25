#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


signed main()
{
    int n; cin>>n;
    int x; cin>>x;
    vector<pair<int,int>> v;

    for (int i=0; i<n; ++i)
    {
        int e; cin>>e;
        v.push_back({e,i+1});
    }

    sort(v.begin(),v.end());

    int l=0; int r=n-1;

    int pa=-1; int pb=-1;

    while(l<r)
    {
        int t=v[l].first + v[r].first;

        if (t<x){l++;}
        else if (t>x){r--;}
        else {pa = v[l].second; pb=v[r].second; break;}
    }

    if (pa==-1){cout << "IMPOSSIBLE" << endl;}
    else 
    {
        cout << pa << " " << pb << endl;
    }
    return 0;
}
