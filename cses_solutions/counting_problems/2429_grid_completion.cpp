#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 1e9 + 7;
const int MAXN = 505;

ll fact[MAXN], invfact[MAXN];

// BeginCodeSnip{Binary Exponentiation}
ll binpow(ll a, ll b) {
	ll r = 1;
	while (b) {
		if (b & 1) r = r * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return r;
}
// EndCodeSnip
// BeginCodeSnip{Combination Formula}
ll nCr(int n, int r) {
	if (r < 0 || r > n) return 0;
	return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}
// EndCodeSnip
// BeginCodeSnip{Formula from Editorial}
ll formula(int C0, int C1, int C2, int C3, int C4, int C5) {
	ll ans = 0;

	for (int i = 0; i <= min(C0, C3); i++) {

		// Compute sum over j
		ll sumJ = 0;
		for (int j = 0; j <= C1; j++) {
			if (C4 - i - j < 0) continue;

			ll cur = nCr(C1, j) * fact[C4 - i - j] % MOD;
			if (j & 1) cur = (MOD - cur) % MOD;

			sumJ = (sumJ + cur) % MOD;
		}

		// Compute sum over k
		ll sumK = 0;
		for (int k = 0; k <= C2; k++) {
			if (C5 - i - k < 0) continue;

			ll cur = nCr(C2, k) * fact[C5 - i - k] % MOD;
			if (k & 1) cur = (MOD - cur) % MOD;

			sumK = (sumK + cur) % MOD;
		}

		ll cur = 1;
		cur = cur * nCr(C0, i) % MOD;
		cur = cur * nCr(C3, i) % MOD;
		cur = cur * fact[i] % MOD;
		cur = cur * sumJ % MOD;
		cur = cur * sumK % MOD;

		if (i & 1) cur = (MOD - cur) % MOD;

		ans = (ans + cur) % MOD;
	}

	return ans;
}
// EndCodeSnip
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	// BeginCodeSnip{Pre-Compute}
	fact[0] = 1;
	for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;

	invfact[n] = binpow(fact[n], MOD - 2);
	for (int i = n; i > 0; i--) invfact[i - 1] = invfact[i] * i % MOD;
	// EndCodeSnip

	vector<int> p(n, -1), q(n, -1);
	vector<bool> inA(n, false), inB(n, false);

	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < n; j++) {
			if (s[j] == 'A') {
				p[i] = j;
				inA[j] = true;
			}
			if (s[j] == 'B') {
				q[i] = j;
				inB[j] = true;
			}
		}
	}

	int C0 = 0, C1 = 0, C2 = 0, C3 = 0, C4 = 0, C5 = 0;

	for (int i = 0; i < n; i++) {
		if (p[i] == -1 && q[i] == -1) C0++;
		if (p[i] == -1 && q[i] != -1 && !inA[q[i]]) C1++;
		if (p[i] != -1 && q[i] == -1 && !inB[p[i]]) C2++;
	}

	for (int i = 0; i < n; i++) {
		if (!inA[i] && !inB[i]) C3++;
		if (!inA[i]) C4++;
		if (!inB[i]) C5++;
	}

	cout << formula(C0, C1, C2, C3, C4, C5) << "\n";
}
