#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct Line {
    int a, b; // y = ax + b
    Line(int a = 0, int b = 0) : a(a), b(b) {}

    // Compute intersection x-coordinate with another line
    double intersectX(const Line &other) const {
        return (double)(other.b - b) / (a - other.a);
    }

    int value(int x) const {
        return a * x + b;
    }
};

struct Hull {
    deque<Line> dq;

    void add(int a, int b) {
        Line newline(a, b);

        // Keep only the best line for equal slopes (max intercept)
        if (!dq.empty() && dq.back().a == a) {
            if (dq.back().b >= b) return; // old one better
            dq.pop_back(); // new one is better
        }

        while (dq.size() >= 2 && newline.intersectX(dq[dq.size() - 2]) <= dq.back().intersectX(dq[dq.size() - 2])) {
            dq.pop_back();
        }

        dq.push_back(newline);
    }

    int get(int x) {
        while (dq.size() >= 2 && dq[1].value(x) >= dq[0].value(x)) {
            dq.pop_front();
        }
        return dq[0].value(x);
    }
};

int n, m;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    vector<pair<int, int>> segs(n);
    for (int i = 0; i < n; ++i) {
        int y1, y2;
        cin >> y1 >> y2;
        segs[i] = {y1, y2};
    }

    vector<Line> lines;
    for (auto [y1, y2] : segs) {
        int a = y2 - y1;       // slope numerator
        int b = y1 * m;        // intercept scaled
        lines.emplace_back(a, b);
    }

    // Sort lines by slope, break ties with higher intercept first
    sort(lines.begin(), lines.end(), [](const Line &l1, const Line &l2) {
        if (l1.a == l2.a) return l1.b > l2.b;
        return l1.a < l2.a;
    });

    Hull cht;
    for (auto &l : lines) {
        cht.add(l.a, l.b);
    }

    for (int x = 0; x <= m; ++x) {
        int y = cht.get(x);
        cout << y / m << " ";
    }
    cout << endl;
}
