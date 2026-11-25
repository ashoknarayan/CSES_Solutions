#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define MOD 1000000007
#define int long long

int a[200005];
pair<int,int> seg[4*200005];

void build(int ind, int l, int r)
{
    // Base Case
    if (l == r)
    {
        seg[ind] = {a[l],l+1};
        return;
    }
    int m = (l + r) / 2;
    build(2 * ind + 1, l, m);
    build(2 * ind + 2, m + 1, r);
    seg[ind].first = max(seg[2 * ind + 1].first, seg[2 * ind + 2].first);
}

int hotelquery(int val, int ind, int l, int r)
{
    if (seg[ind].first < val)
        return 0;
    if (l==r)
    {
        int ans = seg[ind].second;
        seg[ind].first-=val;
        return ans;
    }
    int res=0;
    int m=(l+r)/2;
    if (seg[2*ind+1].first>=val)
    {
        res = hotelquery(val,2*ind+1,l,m);
    }
    else if (seg[2*ind+2].first>=val)
    {
        res = hotelquery(val,2*ind+2,m+1,r);
    }
    seg[ind].first = max(seg[2 * ind + 1].first, seg[2 * ind + 2].first);
    return res;
}

signed main()
{
    int n; cin >> n;
    int q; cin >> q;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    build(0, 0, n - 1);
    int e;
    while(q--)
    {
        cin>>e;
        cout << hotelquery(e,0,0,n-1) << " ";
    }
    cout << endl;
    return 0;
}
