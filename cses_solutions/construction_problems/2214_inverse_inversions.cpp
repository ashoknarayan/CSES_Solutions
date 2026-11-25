#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;
    cin >> n >> k;

    long long l = 1, r = n;
    vector<long long> result;

    for (long long i = 0; i < n; ++i) {
        if (k >= r - l) {
            // Place r, add (r-l) inversions
            result.push_back(r);
            k -= (r - l);
            r--;
        } else {
            // Place l, add 0 inversions
            result.push_back(l);
            l++;
        }
    }

    for (auto x : result)
        cout << x << " ";
    cout << "\n";

    return 0;
}
