#include <iostream> // For input/output operations (std::cin, std::cout)
#include <vector>   // For std::vector (to store edges, parent array, and component sizes)
#include <algorithm> // For std::sort (to sort edges by weight)
#include <numeric>  // For std::iota (to initialize parent array efficiently)

// Structure to represent an edge in the graph
struct Edge {
    int u, v;     // The two nodes connected by the edge
    int weight;   // The transfer speed (weight) of the connection

    // Custom comparison operator for sorting edges in descending order of weight
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

// --- Disjoint Set Union (DSU) / Union-Find structure ---
std::vector<int> parent;     // parent[i] stores the parent of node i in the DSU tree
std::vector<long long> comp_size; // comp_size[i] stores the size of the component if i is the root

/**
 * @brief Finds the representative (root) of the set containing element i.
 *
 * Implements path compression for optimization.
 *
 * @param i The element whose representative is to be found.
 * @return The representative (root) of the set containing i.
 */
int find_set(int i) {
    if (parent[i] == i) {
        return i; // i is the root of its set
    }
    // Path compression: set parent[i] directly to the root
    return parent[i] = find_set(parent[i]);
}

/**
 * @brief Unions the sets containing elements a and b.
 *
 * Implements union by size for optimization.
 *
 * @param a An element from the first set.
 * @param b An element from the second set.
 * @return True if the sets were different and were united, False otherwise.
 */
bool union_sets(int a, int b) {
    a = find_set(a); // Find root of a's set
    b = find_set(b); // Find root of b's set
    if (a != b) { // If a and b are in different sets
        // Union by size: attach the smaller tree under the root of the larger tree
        if (comp_size[a] < comp_size[b]) {
            std::swap(a, b); // Ensure 'a' is the root of the larger component
        }
        parent[b] = a;       // Make 'a' the parent of 'b's root
        comp_size[a] += comp_size[b]; // Update the size of the merged component
        return true; // Sets were united
    }
    return false; // Sets were already the same
}

/**
 * @brief Solves the problem of summing transfer speeds.
 *
 * Reads graph input, sorts edges by weight, and uses DSU to calculate
 * the total sum of minimum transfer speeds between all pairs of nodes.
 */
void solve() {
    int n; // Number of computers
    std::cin >> n;

    // Store all n-1 edges
    std::vector<Edge> edges(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    // Sort edges in descending order of weight.
    // This is crucial because we want the current edge's weight to be the bottleneck
    // when we consider paths forming between two previously disconnected components.
    std::sort(edges.begin(), edges.end(), std::greater<Edge>());

    // Initialize DSU structure
    parent.resize(n + 1); // Nodes are 1-indexed
    std::iota(parent.begin(), parent.end(), 0); // parent[i] = i for all i
    comp_size.assign(n + 1, 1); // Each component initially has size 1

    long long total_sum_of_min_speeds = 0; // Use long long to prevent overflow

    // Iterate through sorted edges
    for (const auto& edge : edges) {
        int u_root = find_set(edge.u); // Find root of u's component
        int v_root = find_set(edge.v); // Find root of v's component

        // If u and v are in different components (i.e., this edge connects two new components)
        if (u_root != v_root) {
            // The number of pairs that will use this edge as their bottleneck
            // is the product of the sizes of the two components being merged.
            // For each such pair, the minimum transfer speed is 'edge.weight'.
            total_sum_of_min_speeds += (long long)edge.weight * comp_size[u_root] * comp_size[v_root];

            // Union the two components
            union_sets(u_root, v_root);
        }
    }

    // Print the final calculated sum
    std::cout << total_sum_of_min_speeds << "\n";
}

/**
 * @brief Main function where the program execution begins.
 *
 * It optimizes standard I/O streams for faster execution and then calls
 * the `solve` function to handle the problem logic.
 *
 * @return 0 upon successful execution.
 */
int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve(); // Call the solver function

    return 0; // Indicate successful execution.
}

