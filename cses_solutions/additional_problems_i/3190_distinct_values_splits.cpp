#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int n, m=1e9+7, ma=-1;
    cin >> n;
    vector<int> v(n+1), p(n+1,1);
    map<int, int> P;
    for (int i = 1; i <= n; i++){
        cin >> v[i];
        ma = max(ma, P[v[i]] - 1);
        p[i] = ((p[i - 1] - (ma == -1 ? 0 : p[ma]) + m) % m + p[i - 1]) % m;
        P[v[i]] = i;
    }
    cout << (p[n] - p[n - 1] + m) % m << "\n";
}
