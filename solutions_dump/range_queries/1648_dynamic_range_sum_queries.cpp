#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

const int INF = LLONG_MAX;

int a[200005];
int seg[4*100005];

void build(int ind, int l, int r)
{
    // Base Case
    if (l == r)
    {
        seg[ind] = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * ind + 1, l, m);
    build(2 * ind + 2, m + 1, r);
    seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
}


int sumquery(int ind, int l, int r, int L, int R)
{
    // If the range of the segment is completely inside the query range
    if (L <= l && R >= r)
        return seg[ind];
    // If the range of the segment is completely outside the query range
    if (l > R || r < L)
        return 0;
    // Partial overlap case
    int m = (l + r) / 2;
    int lsum = sumquery(2 * ind + 1, l, m, L, R);
    int rsum = sumquery(2 * ind + 2, m + 1, r, L, R);
    return lsum+rsum;
}

void change(int ind, int val, int L, int R, int pos)
{
    if (pos<L || pos>R) return;
    if (pos==L && pos==R) {seg[ind]=val; return;}
    int M=(L+R)/2;
    change(2*ind+1, val,L,M,pos);
    change(2*ind+2, val,M+1,R,pos);
    seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
}

signed main()
{
    int n; cin >> n;
    int q; cin >> q;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    build(0, 0, n - 1);
    int a,b,c;
    while (q--)
    {
        cin>>a>>b>>c;
        if (a==2)
            cout << sumquery(0,0,n-1,b-1,c-1) << endl;
        else
            change(0,c,0,n-1,b-1);
    }
    return 0;
}
//! I have tried most of the function by myself. If it gets Accepted I will be very happy :)
// Same for this too. I have some confidence that this will work.

