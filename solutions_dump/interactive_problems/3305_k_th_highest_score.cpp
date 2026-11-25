#include <iostream>  // For input/output operations
#include <algorithm> // For std::max and std::min

/**
 * @brief Queries the grader for the i-th highest score from a given country.
 * @param country 'F' for Finland, 'S' for Sweden.
 * @param i The 1-indexed rank of the highest score.
 * @return The score received from the grader.
 */
long long query_api(char country, int i) {
    std::cout << country << " " << i << std::endl; // Prints query and flushes output
    long long score;
    std::cin >> score; // Reads response
    return score;
}

int main() {
    // Optimize C++ streams for faster I/O in interactive problems.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k; // n: coders per country, k: desired k-th highest score
    std::cin >> n >> k;

    // Convert k-th highest problem to k'-th smallest: k' = 2*n - k + 1
    int k_prime = 2 * n - k + 1;

    // Binary search for 'i_f': count of elements from Finland in the k'-smallest group.
    // Range for i_f: [max(0, k_prime - n), min(n, k_prime)]
    int low = std::max(0, k_prime - n);
    int high = std::min(n, k_prime);

    long long result_score = -1; // Stores the final k-th highest score

    // Sentinel values for boundary conditions (effectively -infinity and +infinity).
    const long long MIN_SCORE_VAL = 0LL;        // Scores are >= 1
    const long long MAX_SCORE_VAL = 2000000007LL; // Larger than 10^9

    while (low <= high) {
        int i_f = low + (high - low) / 2; // Elements from Finland
        int i_s = k_prime - i_f;         // Elements from Sweden

        // Query the four scores needed for comparison (current and next larger for both countries).
        // For 'i'-th smallest, query (n - i + 1)-th highest.
        long long val_F_current = (i_f == 0) ? MIN_SCORE_VAL : query_api('F', n - i_f + 1);
        long long val_F_next_larger = (i_f == n) ? MAX_SCORE_VAL : query_api('F', n - i_f);
        long long val_S_current = (i_s == 0) ? MIN_SCORE_VAL : query_api('S', n - i_s + 1);
        long long val_S_next_larger = (i_s == n) ? MAX_SCORE_VAL : query_api('S', n - i_s);

        // Binary search logic to adjust the partition.
        if (val_F_current > val_S_next_larger) {
            // Finland's current element is too large, need fewer from Finland.
            high = i_f - 1;
        } else if (val_S_current > val_F_next_larger) {
            // Sweden's current element is too large, need more from Finland.
            low = i_f + 1;
        } else {
            // Correct partition found: k'-th smallest is the max of the two current elements.
            result_score = std::max(val_F_current, val_S_current);
            break;
        }
    }

    // Report the final score and terminate.
    std::cout << "! " << result_score << std::endl;

    return 0;
}
