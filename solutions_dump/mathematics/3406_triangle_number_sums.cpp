#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

vector<int> triangles;

void precompute_triangles() {
    for (int k = 1;; ++k) {
        int t = k * (k + 1) / 2;
        if (t > 1e12) break;
        triangles.push_back(t);
    }
}

bool is_triangle(int n) {
    int d = 8 * n + 1;
    int sq = sqrtl(d);
    return sq * sq == d;
}

int min_triangle_sum(int n) {
    static map<int, int> cache;
    if (cache.count(n)) return cache[n];

    if (is_triangle(n)) return cache[n] = 1;

    for (int t : triangles) {
        if (t >= n) break;
        if (is_triangle(n - t)) return cache[n] = 2;
    }

    return cache[n] = 3;
}

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << min_triangle_sum(n) << endl;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    precompute_triangles();
    solve();
}
