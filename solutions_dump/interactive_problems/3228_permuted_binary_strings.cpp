#include <iostream>
#include <vector>
#include <string>
#include <cmath> // For std::ceil and std::log2 (though we can use bit manipulation)
#include <numeric> // For std::iota if needed, not directly here.

// Function to flush output
void flush_output() {
    std::cout << std::flush;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    if (n == 1) {
        std::cout << "! 1\n";
        flush_output();
        return 0;
    }

    // Calculate k, the number of bits needed to represent values from 0 to n-1.
    // This is equivalent to ceil(log2(n)) if n is a power of 2,
    // or floor(log2(n-1)) + 1 for n > 1.
    // For n=2, values are {0,1}, need 1 bit. log2(1)+1 = 1.
    // For n=3, values are {0,1,2}, need 2 bits. log2(2)+1 = 2.
    // For n=4, values are {0,1,2,3}, need 2 bits. log2(3)+1 = 2.
    int k = 0;
    int temp_val = n - 1;
    while (temp_val > 0) {
        temp_val >>= 1;
        k++;
    }

    // This array will store (a_i - 1)
    std::vector<int> a_minus_1(n, 0);

    // Perform k queries
    for (int j = 0; j < k; ++j) {
        std::string query_str(n, '0');
        for (int i = 0; i < n; ++i) {
            // (i + 1) is the actual number from 1 to n.
            // We want the j-th bit of (i + 1 - 1), which is i.
            if (((i >> j) & 1)) {
                query_str[i] = '1';
            }
        }

        std::cout << "? " << query_str << "\n";
        flush_output();

        std::string response_str;
        std::cin >> response_str;

        for (int i = 0; i < n; ++i) {
            if (response_str[i] == '1') {
                // If the j-th bit of a_i is 1, add 2^j to a_i - 1
                a_minus_1[i] += (1 << j);
            }
        }
    }

    // Report the final permutation
    std::cout << "! ";
    for (int i = 0; i < n; ++i) {
        std::cout << (a_minus_1[i] + 1) << (i == n - 1 ? "" : " ");
    }
    std::cout << "\n";
    flush_output();

    return 0;
}
