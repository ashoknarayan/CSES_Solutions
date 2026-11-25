#include <iostream>
#include <vector>
 
using namespace std;
 
const int MAXN = 200100, MOD = (int)1e9 + 7;
int n, cnt[MAXN], p2[MAXN];
bool isprime[MAXN];
vector<int> primes;
 
void init() {
    fill(isprime, isprime + MAXN, true);
    primes = {2};
    for (int p = 3; p < MAXN; p += 2) {
        if (!isprime[p])
            continue;
        primes.push_back(p);
        for (long long k = 1ll * p * p; k < MAXN; k += 2 * p)
            isprime[k] = false;
    }
}
int main() {
    ios::sync_with_stdio(false);
    init();
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        ++cnt[x];
    }
    p2[0] = 1;
    for (int i = 1; i <= n; ++i)
        p2[i] = (2 * p2[i - 1]) % MOD;
    for (int i = 0; primes[i] <= n; ++i) {
        for (int j = n / primes[i]; j >= 1; --j) {
            cnt[j] += cnt[j * primes[i]];
        }
    }
    for (int i = 1; i <= n; ++i)
        cnt[i] = p2[cnt[i]] - 1;
    for (int i = 0; primes[i] <= n; ++i) {
        for (int j = 1; j * primes[i] <= n; ++j) {
            cnt[j] -= cnt[j * primes[i]];
            if (cnt[j] < 0)
                cnt[j] += MOD;
        }
    }
    for (int i = 1; i <= n; ++i)
        cout << cnt[i] << " ";
    cout << endl;
    return 0;
}
