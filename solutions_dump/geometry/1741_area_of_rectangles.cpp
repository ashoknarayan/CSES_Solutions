#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Event {
    int x, y1, y2, type; // +1 for entering, -1 for leaving
    bool operator<(const Event &e) const {
        return x < e.x;
    }
};

const int MAXN = 4e5;
vector<int> y_coords;
int cnt[MAXN * 4], len[MAXN * 4];

void update(int node, int l, int r, int ul, int ur, int type) {
    if (r < ul || ur < l) return;
    if (ul <= l && r <= ur) {
        cnt[node] += type;
    } else {
        int mid = (l + r) / 2;
        update(node * 2, l, mid, ul, ur, type);
        update(node * 2 + 1, mid + 1, r, ul, ur, type);
    }

    if (cnt[node]) {
        len[node] = y_coords[r + 1] - y_coords[l];
    } else {
        len[node] = (l == r ? 0 : len[node * 2] + len[node * 2 + 1]);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<Event> events;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        events.push_back({x1, y1, y2, 1});
        events.push_back({x2, y1, y2, -1});
        y_coords.push_back(y1);
        y_coords.push_back(y2);
    }

    // Coordinate compression on y
    sort(y_coords.begin(), y_coords.end());
    y_coords.erase(unique(y_coords.begin(), y_coords.end()), y_coords.end());

    auto getY = [&](int y) {
        return lower_bound(y_coords.begin(), y_coords.end(), y) - y_coords.begin();
    };

    for (auto &e : events) {
        e.y1 = getY(e.y1);
        e.y2 = getY(e.y2) - 1; // y2 is exclusive, so we mark till y2 - 1
    }

    sort(events.begin(), events.end());

    int prev_x = events[0].x;
    int area = 0;
    for (auto &e : events) {
        int dx = e.x - prev_x;
        area += len[1] * dx;
        update(1, 0, y_coords.size() - 2, e.y1, e.y2, e.type);
        prev_x = e.x;
    }

    cout << area << '\n';
}
