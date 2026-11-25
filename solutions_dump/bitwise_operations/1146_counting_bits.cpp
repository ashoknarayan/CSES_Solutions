#include <bits/stdc++.h>
using namespace std;
#define int long long

int countTotalBits(int n) {
    int count = 0;
    for (int i = 0; (1LL << i) <= n; i++) {
        int cycle_len = 1LL << (i + 1);  // 2^(i+1)
        int full_cycles = (n + 1) / cycle_len;
        int ones_in_full_cycles = full_cycles * (1LL << i);
        int remainder = (n + 1) % cycle_len;
        int extra_ones = max(0LL, remainder - (1LL << i));
        count += ones_in_full_cycles + extra_ones;
    }
    return count;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    cout << countTotalBits(n) << '\n';
}
