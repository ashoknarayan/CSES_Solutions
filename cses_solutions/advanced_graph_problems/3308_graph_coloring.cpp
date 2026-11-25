#include <iostream>
#include <vector>
#include <algorithm>
#include <set> // For adjacency list representation from edges

using namespace std;

const int MAXN = 16;

// Adjacency matrix is often more convenient for bitmask DP
bool adj_matrix[MAXN][MAXN]; 

// dp[mask] = minimum colors for subgraph represented by mask
int dp[1 << MAXN]; 

// is_independent[mask] = true if mask represents an independent set
bool is_independent[1 << MAXN];

// To store one valid coloring
int node_colors[MAXN]; 

// To reconstruct the coloring: store the independent set used for dp[mask]
int first_color_set[1 << MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        // Adjust to 0-indexed for bitmasks
        --u; --v; 
        adj_matrix[u][v] = true;
        adj_matrix[v][u] = true;
    }

    // 1. Precompute all independent sets
    // A mask represents a set of vertices.
    // (1 << i) is the i-th vertex.
    for (int mask = 0; mask < (1 << n); ++mask) {
        bool current_set_is_independent = true;
        for (int i = 0; i < n; ++i) {
            if (!((mask >> i) & 1)) continue; // If i-th bit not set in mask

            for (int j = i + 1; j < n; ++j) { // Check for edges between pairs in the set
                if (((mask >> j) & 1) && adj_matrix[i][j]) {
                    current_set_is_independent = false;
                    break;
                }
            }
            if (!current_set_is_independent) break;
        }
        is_independent[mask] = current_set_is_independent;
    }

    // 2. Dynamic Programming to find minimum colors
    dp[0] = 0; // Empty set needs 0 colors

    for (int mask = 1; mask < (1 << n); ++mask) {
        dp[mask] = n + 1; // Initialize with a value greater than n (max possible colors)
        
        // Iterate through all submasks of 'mask'
        // A common trick to iterate submasks:
        // for (int submask = mask; submask > 0; submask = (submask - 1) & mask)
        // This ensures 'submask' is always a submask of 'mask'
        for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
            if (is_independent[submask]) {
                if (1 + dp[mask ^ submask] < dp[mask]) {
                    dp[mask] = 1 + dp[mask ^ submask];
                    first_color_set[mask] = submask; // Store which independent set got the first color
                }
            }
        }
    }

    // Output the minimum number of colors
    cout << dp[(1 << n) - 1] << endl;

    // 3. Reconstruct the coloring
    int current_mask = (1 << n) - 1;
    int color_val = 1;
    while (current_mask > 0) {
        int independent_set_mask = first_color_set[current_mask];
        for (int i = 0; i < n; ++i) {
            if ((independent_set_mask >> i) & 1) { // If i-th vertex is in this independent set
                node_colors[i] = color_val;
            }
        }
        current_mask ^= independent_set_mask; // Remove colored vertices from the mask
        color_val++; // Next color
    }

    // Output the colors (adjust back to 1-indexed for output)
    for (int i = 0; i < n; ++i) {
        cout << node_colors[i] << (i == n - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}
