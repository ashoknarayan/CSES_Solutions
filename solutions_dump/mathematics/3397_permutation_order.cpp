#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> factorial(21);

// Precompute factorials
void precompute_factorials() {
    factorial[0] = 1;
    for (int i = 1; i <= 20; ++i)
        factorial[i] = factorial[i - 1] * i;
}

// Find k-th permutation (1-indexed)
vector<int> get_permutation(int n, int k) {
    vector<int> nums, result;
    for (int i = 1; i <= n; ++i) nums.push_back(i);
    --k; // 0-based indexing

    for (int i = 0; i < n; ++i) {
        int f = factorial[n - 1 - i];
        int idx = k / f;
        result.push_back(nums[idx]);
        nums.erase(nums.begin() + idx);
        k %= f;
    }
    return result;
}

// Find index (1-indexed) of permutation
int get_index(int n, vector<int> perm) {
    vector<int> nums;
    for (int i = 1; i <= n; ++i) nums.push_back(i);
    int k = 0;

    for (int i = 0; i < n; ++i) {
        int pos = find(nums.begin(), nums.end(), perm[i]) - nums.begin();
        k += pos * factorial[n - 1 - i];
        nums.erase(nums.begin() + pos);
    }
    return k + 1;
}

void solve() {
    precompute_factorials();
    int t;
    cin >> t;
    while (t--) {
        int type;
        cin >> type;
        if (type == 1) {
            int n, k;
            cin >> n >> k;
            vector<int> perm = get_permutation(n, k);
            for (int x : perm) cout << x << ' ';
            cout << '\n';
        } else {
            int n;
            cin >> n;
            vector<int> perm(n);
            for (int i = 0; i < n; ++i) cin >> perm[i];
            cout << get_index(n, perm) << '\n';
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
