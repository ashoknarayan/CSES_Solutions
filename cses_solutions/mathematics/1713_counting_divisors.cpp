#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 1;

int divisors[N];

signed main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);

    for (int i = 1; i < N; ++i) {
        for (int j = i; j < N; j += i) {
            divisors[j]++;
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        cout << divisors[n] << endl;
    }

    return 0;
}
