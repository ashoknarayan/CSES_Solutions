#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

// Fast input
inline void fastscan(int &x) {
    x = 0; char ch = getchar_unlocked(); int neg = 0;
    while (ch < '0' || ch > '9') { if (ch == '-') neg = 1; ch = getchar_unlocked(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar_unlocked(); }
    if (neg) x = -x;
}

const int MAXN = 1e7 + 5;
const int NMAX = 1 << 24; // Next power of two above 1e7
int A[MAXN];
int ST[NMAX << 1];  // full binary tree size = 2*N

int n, k;
int x, a, b, c;

signed main() {
    fastscan(n); fastscan(k);
    fastscan(x); fastscan(a); fastscan(b); fastscan(c);

    // Generate the array
    A[0] = x;
    for (int i = 1; i < n; ++i)
        A[i] = (a * A[i - 1] + b) % c;

    // Build segment tree bottom-up
    int base = 1;
    while (base < n) base <<= 1;
    for (int i = 0; i < n; ++i)
        ST[base + i] = A[i];
    for (int i = base - 1; i > 0; --i)
        ST[i] = ST[i << 1] | ST[i << 1 | 1];

    // Process window ORs and XOR all
    int ans = 0;
    for (int i = 0; i <= n - k; ++i) {
        int l = base + i;
        int r = base + i + k - 1;
        int orval = 0;
        while (l <= r) {
            if (l & 1) orval |= ST[l++];
            if (!(r & 1)) orval |= ST[r--];
            l >>= 1; r >>= 1;
        }
        ans ^= orval;
    }

    cout << ans << endl;
}
