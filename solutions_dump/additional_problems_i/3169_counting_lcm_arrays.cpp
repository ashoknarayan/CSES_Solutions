#include <iostream>
#include <vector>
#include <map>

// Define the modulus for all calculations.
const int MOD = 1e9 + 7;

// A 2x2 matrix structure for our dynamic programming state transitions.
struct Matrix {
    long long mat[2][2];

    Matrix() {
        mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0;
    }
};

// Function to multiply two 2x2 matrices under the given modulus.
Matrix multiply(Matrix A, Matrix B) {
    Matrix C;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int l = 0; l < 2; l++) {
                C.mat[i][j] = (C.mat[i][j] + A.mat[i][l] * B.mat[l][j]) % MOD;
            }
        }
    }
    return C;
}

// Function to compute matrix exponentiation (A^p) using binary exponentiation.
Matrix power(Matrix A, long long p) {
    Matrix res;
    res.mat[0][0] = res.mat[1][1] = 1; // Start with the identity matrix.

    while (p > 0) {
        if (p & 1) {
            res = multiply(res, A);
        }
        A = multiply(A, A);
        p >>= 1;
    }
    return res;
}

// Main logic to solve a single test case.
void solve() {
    long long n, k;
    std::cin >> n >> k;

    // The condition is on pairs (a_i, a_{i+1}), so we need at least 2 elements.
    if (n < 2) {
        // This case is ruled out by constraints, but as a base case,
        // any single divisor of k would be a valid array of length 1.
        // We handle it just in case, though for n>=2 it's not needed.
        // For n=1, the number of arrays is the number of divisors of k.
        // But since n>=2, we proceed.
    }

    // Step 1: Prime factorize k to get p_j^e_j.
    std::map<long long, int> prime_factors;
    long long temp_k = k;
    for (long long i = 2; i * i <= temp_k; i++) {
        if (temp_k % i == 0) {
            while (temp_k % i == 0) {
                prime_factors[i]++;
                temp_k /= i;
            }
        }
    }
    if (temp_k > 1) {
        prime_factors[temp_k]++;
    }

    long long total_ans = 1;
    long long power_n = n - 1;

    // Step 2: For each prime factor, calculate the number of valid exponent sequences.
    for (auto const& [p, e] : prime_factors) {
        // The problem for each prime is to count sequences c_1, ..., c_n
        // where 0 <= c_i <= e and max(c_i, c_{i+1}) = e.
        
        // We set up a DP with two states:
        // State 0: sequence ends with an exponent < e.
        // State 1: sequence ends with an exponent == e.
        // The transition matrix M is:
        // M = [[0, e],
        //      [1, 1]]
        Matrix M;
        M.mat[0][0] = 0;
        M.mat[0][1] = e;
        M.mat[1][0] = 1;
        M.mat[1][1] = 1;

        // Step 3: Use matrix exponentiation to find the transitions over n-1 steps.
        Matrix M_final = power(M, power_n);

        // The initial state for a sequence of length 1 is:
        // dp[1][0] = e (choices 0, 1, ..., e-1)
        // dp[1][1] = 1 (choice e)
        // So, the initial vector is [e, 1]^T.
        
        // Calculate the final number of sequences of length n.
        long long dp_n_0 = (M_final.mat[0][0] * e + M_final.mat[0][1] * 1) % MOD;
        long long dp_n_1 = (M_final.mat[1][0] * e + M_final.mat[1][1] * 1) % MOD;
        
        long long count_for_prime = (dp_n_0 + dp_n_1) % MOD;
        
        // Step 4: Multiply the results for each prime factor.
        total_ans = (total_ans * count_for_prime) % MOD;
    }
    
    std::cout << total_ans << "\n";
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
