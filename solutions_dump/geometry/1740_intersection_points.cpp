#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define endl '\n'

// Binary Indexed Tree (Fenwick Tree)
struct BIT {
    vector<int> bit;
    int n;

    BIT(int _n) : n(_n) {
        bit.assign(n + 2, 0);
    }

    void update(int i, int delta) {
        for (++i; i < (int)bit.size(); i += i & -i)
            bit[i] += delta;
    }

    int query(int i) {
        int res = 0;
        for (++i; i > 0; i -= i & -i)
            res += bit[i];
        return res;
    }

    int query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    struct Horizontal { int x1, x2, y; };
    struct Vertical { int x, y1, y2; };

    vector<Horizontal> horizontals;
    vector<Vertical> verticals;
    vector<int> all_y;

    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (y1 == y2) {
            if (x1 > x2) swap(x1, x2);
            horizontals.push_back({x1, x2, y1});
            all_y.push_back(y1);
        } else if (x1 == x2) {
            if (y1 > y2) swap(y1, y2);
            verticals.push_back({x1, y1, y2});
            all_y.push_back(y1);
            all_y.push_back(y2);
        }
    }

    // Coordinate compression of y
    sort(all_y.begin(), all_y.end());
    all_y.erase(unique(all_y.begin(), all_y.end()), all_y.end());

    auto compress = [&](int y) {
        return lower_bound(all_y.begin(), all_y.end(), y) - all_y.begin();
    };

    int ysize = all_y.size();
    BIT bit(ysize);

    // Create events
    struct Event {
        int x, type; // 0 = open, 1 = query, 2 = close
        int y1, y2;
    };

    vector<Event> events;

    for (auto& h : horizontals) {
        int cy = compress(h.y);
        // Note: we add at x1 + 1 and remove at x2 to avoid counting endpoints
        events.push_back({h.x1 + 1, 0, cy, cy});
        events.push_back({h.x2, 2, cy, cy});
    }

    for (auto& v : verticals) {
        int cy1 = compress(v.y1);
        int cy2 = compress(v.y2);
        events.push_back({v.x, 1, cy1, cy2});
    }

    // Sort events by x, then by type (open < query < close)
    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.type < b.type;
    });

    int ans = 0;
    for (auto& e : events) {
        if (e.type == 0) {
            bit.update(e.y1, 1);
        } else if (e.type == 2) {
            bit.update(e.y1, -1);
        } else {
            // Query in (y1, y2) → exclude y1 and y2 (no endpoints)
            ans += bit.query(e.y1 + 1, e.y2 - 1);
        }
    }

    cout << ans << endl;
    return 0;
}
