#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

const int INF = LLONG_MAX; // Define an appropriate value for infinity

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
    seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
}

int query(int ind, int l, int r, int L, int R)
{
    // If the range of the segment is completely inside the query range
    if (L <= l && R >= r)
        return seg[ind];
    // If the range of the segment is completely outside the query range
    if (l > R || r < L)
        return INF;
    // Partial overlap case
    int m = (l + r) / 2;
    int lmin = query(2 * ind + 1, l, m, L, R);
    int rmin = query(2 * ind + 2, m + 1, r, L, R);
    return min(lmin, rmin);
}

signed main()
{
    int n; cin >> n;
    int q; cin >> q;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    build(0, 0, n - 1);
    int L, R;
    while (q--)
    {
        cin >> L >> R;
        // Since input is 1-based index, convert to 0-based index
        cout << query(0, 0, n - 1, L - 1, R - 1) << endl;
    }
    return 0;
}
/*
I have used help from ChatGPT to get this.
I can refer this for segment trees.

*/
