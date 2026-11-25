#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int INF = 1e18;
const int MAX = 1 << 17; // covers up to 1e5

struct Line {
    mutable int a, b, xRight;
    bool operator<(const Line& o) const { return a < o.a; }
    bool operator<(int x) const { return xRight < x; }
};

// Convex hull container for max queries
struct Hull : multiset<Line, less<>> {
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->xRight = INF, false;
        if (x->a == y->a) x->xRight = (x->b > y->b ? INF : -INF);
        else x->xRight = (y->b - x->b) / (x->a - y->a);
        return x->xRight >= y->xRight;
    }

    void insertLine(int a, int b) {
        auto z = insert({a, b, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->xRight >= y->xRight)
            isect(x, erase(y));
    }

    int query(int x) {
        if (empty()) return -1;
        return lower_bound(x)->a * x + lower_bound(x)->b;
    }
};

Hull seg[MAX * 2]; // segment tree

void addLine(int l, int r, int a, int b, int i = 1, int tl = 0, int tr = MAX - 1) {
    if (r < tl || tr < l) return;
    if (l <= tl && tr <= r) {
        seg[i].insertLine(a, b);
        return;
    }
    int tm = (tl + tr) / 2;
    addLine(l, r, a, b, i * 2, tl, tm);
    addLine(l, r, a, b, i * 2 + 1, tm + 1, tr);
}

int query(int x, int i = 1, int tl = 0, int tr = MAX - 1) {
    int res = seg[i].query(x);
    if (tl == tr) return res;
    int tm = (tl + tr) / 2;
    if (x <= tm)
        return max(res, query(x, i * 2, tl, tm));
    else
        return max(res, query(x, i * 2 + 1, tm + 1, tr));
}

int n, m;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        int dx = x2 - x1;
        int dy = y2 - y1;
        int slope = dy / dx;
        int intercept = y1 - slope * x1;

        addLine(x1, x2, slope, intercept);
    }

    for (int x = 0; x <= m; ++x) {
        cout << query(x) << " ";
    }
    cout << endl;
}
