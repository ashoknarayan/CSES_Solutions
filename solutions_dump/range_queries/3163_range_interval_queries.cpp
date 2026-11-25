#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct WaveletTree {
    int lo, hi;
    WaveletTree *l = nullptr, *r = nullptr;
    vector<int> b;

    WaveletTree(vector<int>::iterator from, vector<int>::iterator to, int x, int y) {
        lo = x, hi = y;
        if (lo == hi || from >= to) return;

        int mid = (lo + hi) / 2;
        auto f = [mid](int x) { return x <= mid; };
        b.reserve(to - from + 1);
        b.push_back(0);
        for (auto it = from; it != to; ++it)
            b.push_back(b.back() + f(*it));

        auto pivot = stable_partition(from, to, f);
        l = new WaveletTree(from, pivot, lo, mid);
        r = new WaveletTree(pivot, to, mid + 1, hi);
    }

    int range(int lpos, int rpos, int k1, int k2) {
        if (k2 < lo || hi < k1 || lpos > rpos) return 0;
        if (k1 <= lo && hi <= k2) return rpos - lpos + 1;
        int left_l = b[lpos - 1], left_r = b[rpos];
        return l->range(left_l + 1, left_r, k1, k2) +
               r->range(lpos - left_l, rpos - left_r, k1, k2);
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> x(n + 1), all;

    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
        all.push_back(x[i]);
    }

    // Coordinate compression using sorted unique vector
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());

    auto get = [&](int val) -> int {
        return lower_bound(all.begin(), all.end(), val) - all.begin() + 1;
    };

    for (int i = 1; i <= n; ++i) x[i] = get(x[i]);

    WaveletTree wt(x.begin() + 1, x.end(), 1, all.size());

    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        int c1 = lower_bound(all.begin(), all.end(), c) - all.begin() + 1;
        int d1 = upper_bound(all.begin(), all.end(), d) - all.begin();

        if (c1 > d1) {
            cout << 0 << endl;
        } else {
            cout << wt.range(a, b, c1, d1) << endl;
        }
    }
}
