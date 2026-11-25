#pragma GCC optimize("O3,unroll-loops,inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt")
#include <bits/stdc++.h>
using namespace std;
 
pair<int, int> stone[1100];
int H[100], S[100], K[100], dp[100001];
 
int stone_cnt, n, T;
 
void add_stone(int w, int m, int c) {
    for (int i = 0; (1 << i) <= c; i++) {
        stone[stone_cnt++] = {w << i, m << i};
        c -= (1 << i);
    }
    if (c > 0) stone[stone_cnt++] = {w * c, m * c};
}
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> T;
    for (int i = 0; i < n; i++) cin >> H[i];
    for (int i = 0; i < n; i++) cin >> S[i];
    for (int i = 0; i < n; i++) cin >> K[i];
    for (int i = 0; i < n; i++) add_stone(H[i], S[i], K[i]);
    for (int i = 0; i < stone_cnt; i++) {
        for (int w = 0; w + stone[i].first <= T; w++) {
            dp[w] = max(dp[w], dp[w + stone[i].first] + stone[i].second);
        }
    }
    cout << dp[0];
    return 0;
}
