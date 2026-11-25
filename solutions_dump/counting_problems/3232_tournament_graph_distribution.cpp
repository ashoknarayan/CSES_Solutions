#include <iostream>
#include <vector>

using namespace std;

// Constants and global arrays for DP
const int MAXN = 501;
const int MOD = 1e9 + 7;

long long C[MAXN][MAXN];       // Stores binomial coefficients C(n, k)
long long p2[MAXN * MAXN / 2]; // Stores powers of 2
long long T[MAXN];             // Stores T[i], the total number of tournaments on i nodes
long long S[MAXN];             // Stores S[i], the number of strongly connected tournaments on i nodes
long long dp[MAXN][MAXN];      // Stores dp[i][j], the number of tournaments on i nodes with j SCCs

/**
 * @brief Precomputes binomial coefficients using Pascal's identity.
 *
 * C[i][j] = C[i-1][j-1] + C[i-1][j]
 * Time Complexity: O(n^2)
 */
void precompute_combi(int n) {
    C[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }
}

/**
 * @brief Precomputes powers of 2 up to 2^(n*(n-1)/2).
 *
 * Time Complexity: O(n^2)
 */
void precompute_powers(int n) {
    p2[0] = 1;
    int max_power = n * (n - 1) / 2;
    for (int i = 1; i <= max_power; ++i) {
        p2[i] = (p2[i - 1] * 2) % MOD;
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // --- 1. Precomputation Phase ---
    precompute_combi(n);
    precompute_powers(n);

    // --- 2. Calculate T[i] and S[i] ---

    // Calculate T[i] = 2^(i*(i-1)/2)
    T[0] = 1;
    for (int i = 1; i <= n; ++i) {
        T[i] = p2[i * (i - 1) / 2];
    }

    // Calculate S[i] using its recurrence relation
    S[0] = 0;
    for (int i = 1; i <= n; ++i) {
        S[i] = T[i];
        for (int j = 1; j < i; ++j) {
            long long term = (C[i][j] * S[j]) % MOD;
            term = (term * T[i - j]) % MOD;
            S[i] = (S[i] - term + MOD) % MOD; // Add MOD to handle negative results
        }
    }

    // --- 3. Main DP Calculation ---

    // Base case: 0 nodes, 0 SCCs -> 1 way (the empty graph)
    dp[0][0] = 1;

    // Fill the dp table
    for (int j = 1; j <= n; ++j) {         // Number of SCCs
        for (int i = j; i <= n; ++i) {     // Number of total nodes
            // The first SCC can have size s, from 1 to i-(j-1)
            for (int s = 1; s <= i - j + 1; ++s) {
                // Choose s nodes for the first SCC: C(i, s)
                // Form a strongly connected tournament on them: S[s]
                // Form the rest of the graph on i-s nodes with j-1 SCCs: dp[i-s][j-1]
                long long term = (C[i][s] * S[s]) % MOD;
                term = (term * dp[i - s][j - 1]) % MOD;
                dp[i][j] = (dp[i][j] + term) % MOD;
            }
        }
    }

    // --- 4. Output Results ---
    for (int k = 1; k <= n; ++k) {
        cout << dp[n][k] << "\n";
    }

    return 0;
}
