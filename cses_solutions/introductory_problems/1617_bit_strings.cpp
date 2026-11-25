#include <bits/stdc++.h>
using namespace std;
#define loop(i,a,b,s) for (int i=a; i!=b; i+=s)
typedef long long ll;

const ll MOD = 1e9 + 7;

ll power(ll x, ll y) {
    ll res = 1;
    x %= MOD;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % MOD;
        y >>= 1;
        x = (x * x) % MOD;
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    cout << power(2, n) << endl;
    return 0;
}
