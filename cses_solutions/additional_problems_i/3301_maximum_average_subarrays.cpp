#include <iostream>
#include <vector>
using namespace std;

using int128 = __int128_t;
vector<long long> p;

int128 cross(int a, int b, int c) {
    // Compare slopes (p[b-1] - p[a-1]) / (b - a) vs (p[c-1] - p[b-1]) / (c - b)
    // cross product to check convexity
    return (int128)(p[b - 1] - p[a - 1]) * (c - b) - (int128)(p[c - 1] - p[b - 1]) * (b - a);
}

int128 compare_slope(int k1, int k2, int i) {
    int128 v1 = (int128)(p[i] - p[k1 - 1]) * (i - (k2 - 1));
    int128 v2 = (int128)(p[i] - p[k2 - 1]) * (i - (k1 - 1));
    if (v1 > v2) return 1;
    if (v1 < v2) return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    p.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        long long x;
        cin >> x;
        p[i] = p[i - 1] + x;
    }

    vector<int> hull;
    hull.push_back(1); // We store k = i + 1, and refer to point (k-1, p[k-1])

    for (int i = 1; i <= n; ++i) {
        // Binary search to find best k
        int low = 0, high = hull.size() - 1;
        while (low < high) {
            int mid = (low + high) / 2;
            if (compare_slope(hull[mid], hull[mid + 1], i) < 0)
                low = mid + 1;
            else
                high = mid;
        }

        int k = hull[low]; // best k such that subarray [k..i] has max avg
        cout << (i - k + 1) << (i == n ? '\n' : ' ');

        // Maintain upper hull
        while (hull.size() >= 2) {
            int m1 = hull[hull.size() - 2];
            int m2 = hull[hull.size() - 1];
            if (cross(m1, m2, i + 1) >= 0)
                hull.pop_back();
            else
                break;
        }
        hull.push_back(i + 1);
    }

    return 0;
}
