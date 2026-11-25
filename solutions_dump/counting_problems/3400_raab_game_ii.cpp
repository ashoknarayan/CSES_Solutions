#include <bits/stdc++.h>
using namespace std;

namespace lib {
  const int MOD = 1e9 + 7;
  struct mint {
    int val;
    mint(long long v = 0) { 
      val = int(v % MOD); 
      if (val < 0) val += MOD;
    }
    mint& operator+=(const mint &other) { 
      if ((val += other.val) >= MOD) val -= MOD; 
      return *this;
    }
    mint& operator*=(const mint &other) {
      val = int((1LL * val * other.val) % MOD); 
      return *this;
    }
    mint operator*(const mint &other) const { return mint(*this) *= other; }
    mint operator+(const mint &other) const { return mint(*this) += other; }

    static vector<mint> fact, ifact;
    static void init(int n) {
      fact.assign(n + 1, 1);
      ifact.assign(n + 1, 1);
      for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i;
      ifact[n] = mint(inv(fact[n].val));
      for (int i = n - 1; i >= 0; --i)
        ifact[i] = ifact[i + 1] * (i + 1);
    }
    static int inv(int a) {
      int res = 1, b = MOD - 2;
      while (b) {
        if (b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
      }
      return res;
    }
    static mint binom(int n, int k) {
      if (k < 0 || k > n) return 0;
      return fact[n] * ifact[k] * ifact[n - k];
    }
    static mint fact_val(int n) {
      return fact[n];
    }
  };
  vector<mint> mint::fact, mint::ifact;
}

lib::mint f[5001][5001];

struct Derangement {
  Derangement() {
    lib::mint::init(5000);
    f[0][0] = 1;
    for (int i = 0; i <= 5000; ++i) {
      for (int j = 0; j <= 5000; ++j) {
        if (j + 1 <= 5000) f[i][j + 1] += f[i][j] * i;                    // i beats j+1
        if (i + 1 <= 5000) f[i + 1][j] += f[i][j] * j;                    // j beats i+1
        if (i + 1 <= 5000 && j + 1 <= 5000) f[i + 1][j + 1] += f[i][j] * (i + j + 1); // tie
      }
    }
  }
} Derangement;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n, a, b;
    cin >> n >> a >> b;
    if (a + b > n || (min(a, b) == 0 && max(a, b) != 0)) {
      cout << "0\n";
      continue;
    }

    lib::mint res = f[a][b] * lib::mint::binom(n, a + b) * lib::mint::fact_val(n);
    cout << res.val << "\n";
  }

  return 0;
}
