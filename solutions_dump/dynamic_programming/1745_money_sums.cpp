#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> coins(n);
    int total = 0;
    for (int &x : coins) {
        cin >> x;
        total += x;
    }

    vector<bool> dp(total + 1, false);
    dp[0] = true;

    for (int x : coins) {
        for (int i = total; i >= x; --i) {
            if (dp[i - x]) dp[i] = true;
        }
    }

    vector<int> result;
    for (int i = 1; i <= total; ++i)
        if (dp[i]) result.push_back(i);

    cout << result.size() << endl;
    for (int x : result) cout << x << " ";
    cout << endl;
}
