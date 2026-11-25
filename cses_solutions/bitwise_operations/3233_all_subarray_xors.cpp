#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>

using namespace std;

// The maximum number of bits needed. 2^20 > 10^6, but prefix XORs might need more.
// 21 bits is safe.
const int BITS = 21;

// A structure to manage the linear basis.
struct XorBasis {
    vector<int> basis;

    XorBasis(const vector<int>& a) {
        vector<int> temp_basis(BITS, 0);
        // Step 1: Create a basis in row echelon form
        for (int x : a) {
            for (int i = BITS - 1; i >= 0; --i) {
                if (! (x & (1 << i))) continue;
                if (!temp_basis[i]) {
                    temp_basis[i] = x;
                    break;
                }
                x ^= temp_basis[i];
            }
        }

        // Step 2: Compact the basis into the final vector.
        // **FIX:** Store in descending order of MSB. This makes get_mask work correctly.
        for (int i = BITS - 1; i >= 0; --i) {
            if (temp_basis[i]) {
                basis.push_back(temp_basis[i]);
            }
        }
    }

    // Converts a number into its coordinate vector (mask) w.r.t the basis.
    int get_mask(int x) const {
        int mask = 0;
        for (size_t i = 0; i < basis.size(); ++i) {
            if ((x ^ basis[i]) < x) {
                x ^= basis[i];
                mask |= (1 << i);
            }
        }
        return mask;
    }
};

// Fast Walsh-Hadamard Transform
void fwht(vector<long long>& a, bool inverse) {
    int n = a.size();
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                long long u = a[i + j];
                long long v = a[i + len + j];
                a[i + j] = u + v;
                a[i + len + j] = u - v;
            }
        }
    }
    if (inverse) {
        for (int i = 0; i < n; i++) {
            a[i] /= n;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }

    // 1. Compute prefix XORs
    vector<int> p(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        p[i + 1] = p[i] ^ x[i];
    }

    // Check if a subarray XOR sum of 0 is possible
    bool has_zero_sum = set<int>(p.begin(), p.end()).size() < p.size();

    // 2. Build basis
    XorBasis basis(p);
    int k = basis.basis.size();
    
    if (k == 0) {
        cout << (has_zero_sum ? 1 : 0) << "\n";
        if (has_zero_sum) cout << "0\n";
        return 0;
    }

    // 3. Convert prefixes to masks and prepare for convolution
    int poly_size = 1 << k;
    vector<long long> poly(poly_size, 0);
    for (int val : p) {
        poly[basis.get_mask(val)] = 1;
    }

    // 4. FWHT for XOR convolution
    fwht(poly, false);
    for (int i = 0; i < poly_size; ++i) {
        poly[i] *= poly[i];
    }
    fwht(poly, true);

    // 5. Convert resulting masks back to numbers
    vector<int> result;
    for (int i = 0; i < poly_size; ++i) {
        if (poly[i] > 0) {
            int current_xor_sum = 0;
            for (int j = 0; j < k; ++j) {
                if ((i >> j) & 1) {
                    current_xor_sum ^= basis.basis[j];
                }
            }
            result.push_back(current_xor_sum);
        }
    }

    // Remove 0 if it's not achievable from distinct prefix XORs
    if (!has_zero_sum) {
        auto it = find(result.begin(), result.end(), 0);
        if (it != result.end()) {
            result.erase(it);
        }
    }
    
    sort(result.begin(), result.end());
    
    cout << result.size() << "\n";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << (i == result.size() - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}
