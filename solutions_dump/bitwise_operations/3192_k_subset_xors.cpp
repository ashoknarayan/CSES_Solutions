#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

std::vector<int> build_xor_basis_optimized(const std::vector<int>& arr, int& num_dependent_elements) {
    std::vector<int> basis_msb(30, 0);
    int current_basis_size = 0;
    for (int x : arr) {
        for (int i = 29; i >= 0; --i) {
            if (!((x >> i) & 1)) continue;
            if (basis_msb[i] == 0) {
                basis_msb[i] = x;
                current_basis_size++;
                break;
            }
            x ^= basis_msb[i];
        }
    }
    for (int i = 29; i >= 0; --i) {
        if (basis_msb[i] != 0) {
            for (int j = 29; j >= 0; --j) {
                if (i == j || basis_msb[j] == 0) continue;
                if ((basis_msb[j] >> i) & 1) basis_msb[j] ^= basis_msb[i];
            }
        }
    }
    std::vector<int> final_basis;
    for (int i = 0; i < 30; ++i)
        if (basis_msb[i] != 0) final_basis.push_back(basis_msb[i]);
    std::sort(final_basis.begin(), final_basis.end());
    num_dependent_elements = (int)arr.size() - current_basis_size;
    return final_basis;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    long long k_long;
    std::cin >> n >> k_long;
    int k = (int)k_long;

    std::vector<int> x(n);
    for (int i = 0; i < n; ++i) std::cin >> x[i];

    int num_dependent_elements;
    std::vector<int> basis = build_xor_basis_optimized(x, num_dependent_elements);

    long long multiplicity = 1LL << num_dependent_elements;

    int basis_size = (int)basis.size();
    int max_mask = 1 << basis_size;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    pq.push(0);
    std::vector<bool> visited(max_mask, false);
    visited[0] = true;

    std::vector<int> result;
    result.reserve(k);

    long long current_k_count = 0;
    while (!pq.empty() && current_k_count < k) {
        int mask = pq.top();
        pq.pop();

        int val = 0;
        for (int i = 0; i < basis_size; ++i)
            if ((mask >> i) & 1) val ^= basis[i];

        for (long long i = 0; i < multiplicity && current_k_count < k; ++i) {
            result.push_back(val);
            current_k_count++;
        }
        if (current_k_count >= k) break;

        for (int i = 0; i < basis_size; ++i) {
            int next_mask = mask ^ (1 << i);
            if (!visited[next_mask]) {
                visited[next_mask] = true;
                pq.push(next_mask);
            }
        }
    }

    for (int i = 0; i < k; ++i) {
        std::cout << result[i] << (i == k - 1 ? '\n' : ' ');
    }
    return 0;
}
