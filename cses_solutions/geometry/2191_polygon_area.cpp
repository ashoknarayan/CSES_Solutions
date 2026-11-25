#include<bits/stdc++.h>
using namespace std;


int main()
{
    int n; cin>>n;
    vector<pair<long long,long long>> p;
    pair<long long,long long> pp;
    for (int i=0; i<n; ++i)
    {
        cin>>pp.first>>pp.second;
        p.push_back(pp);
    }
    // ShoeLace Formula
    long long area =0;
    for (long long i=0; i<n; ++i)
        area += (p[i].first * p[(i + 1) % n].second
            - p[(i + 1) % n].first* p[i].second);
    cout << abs(area) << endl;
    return 0;
}
