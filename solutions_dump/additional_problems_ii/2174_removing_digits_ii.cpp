#include <bits/stdc++.h>
using namespace std;
map<long long, pair<long long, long long>> dp[10];
pair<long long, long long> solve(long long max_digit_so_far, long long n) {
    if (n < 10) {
        long long best_digit = max(n, max_digit_so_far);
        return {1, n - best_digit};
    }
    if (dp[max_digit_so_far].count(n))
        return dp[max_digit_so_far][n];
    long long base = 1;
    while (base <= n / 10) base *= 10;
    long long leading_digit = n / base;
    long long remainder = n % base;
    pair<long long, long long> part1 = solve(max(max_digit_so_far, leading_digit), remainder);
    long long new_number = leading_digit * base + part1.second;
    pair<long long, long long> part2 = solve(max_digit_so_far, new_number);
    return dp[max_digit_so_far][n] = {part1.first + part2.first, part2.second};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    cin >> n;
    if (n == 0) {
        cout << 0 << "\n";
        return 0;
    }
    pair<long long, long long> res = solve(0, n);
    cout << res.first << "\n";
}
