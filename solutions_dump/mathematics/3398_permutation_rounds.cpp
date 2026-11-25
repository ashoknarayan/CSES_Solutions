#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int MOD = 1e9 + 7;
const int MAX = 2e5 + 10;

// Sieve for smallest prime factors
vector<int> spf(MAX);
void sieve() {
    iota(spf.begin(), spf.end(), 0);
    for (int i = 2; i * i < MAX; ++i)
        if (spf[i] == i)
            for (int j = i * i; j < MAX; j += i)
                if (spf[j] == j)
                    spf[j] = i;
}

map<int, int> factorize(int x) {
    map<int, int> res;
    while (x > 1) {
        int f = spf[x];
        int cnt = 0;
        while (x % f == 0) {
            x /= f;
            cnt++;
        }
        res[f] = cnt;
    }
    return res;
}

int modpow(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void solve(){
    int n;
    cin >> n;
    vector<int> p(n);
    for (int &x : p) cin >> x, --x;

    vector<bool> vis(n, false);
    map<int, int> prime_powers; // max power of each prime

    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            int len = 0, j = i;
            while (!vis[j]) {
                vis[j] = true;
                j = p[j];
                len++;
            }

            auto factors = factorize(len);
            for (auto [prime, cnt] : factors)
                prime_powers[prime] = max(prime_powers[prime], cnt);
        }
    }

    int ans = 1;
    for (auto [prime, cnt] : prime_powers)
        ans = ans * modpow(prime, cnt) % MOD;

    cout << ans << endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    sieve();
    solve();
}
