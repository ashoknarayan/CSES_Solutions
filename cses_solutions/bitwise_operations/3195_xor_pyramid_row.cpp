#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> A(n);
    for (int &x : A) {cin >> x;}
    int r = n - k;
    int c = n;
    for (int p = 0; p < 20; ++p) {
        if ((r >> p) & 1) {
            int d = 1 << p;
            for (int i = 0; i < c - d; ++i) A[i] = A[i] ^ A[i + d];
            c -= d;
        }
    }
    for (int i = 0; i < k; ++i) cout << A[i] << ' ';
    cout << '\n';
    return 0;
}

// gemini slayed
