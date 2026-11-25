#include <iostream> // For input/output operations (std::cin, std::cout)
#include <vector>   // For std::vector (to store edges, parent array, component sizes, and results)
#include <algorithm> // For std::sort (to sort edges by weight)
#include <numeric>  // For std::iota (to initialize parent array efficiently)

// Structure to represent an edge in the graph
struct Edge {
    int u, v;          // The two nodes connected by the edge
    int weight;        // The weight (cost) of the connection
    int original_index; // The 0-based index of this edge as it appeared in the input

    // Custom comparison operator for sorting edges in ascending order of weight.
    // If weights are equal, maintain a consistent order (e.g., by original_index)
    // to ensure predictable iteration, though for this problem's logic, any consistent
    // tie-breaking among equal weights is fine within a block.
    bool operator<(const Edge& other) const {
        if (weight != other.weight) {
            return weight < other.weight;
        }
        return original_index < other.original_index; // Tie-break by original index
    }
};

// --- Disjoint Set Union (DSU) / Union-Find structure ---
std::vector<int> parent;     // parent[i] stores the parent of node i in the DSU tree
std::vector<int> comp_size; // comp_size[i] stores the size of the component if i is the root

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
void union_sets(int a, int b) {
    a = find_set(a); // Find root of a's set
    b = find_set(b); // Find root of b's set
    if (a != b) { // If a and b are in different sets
        // Union by size: attach the smaller tree under the root of the larger tree
        if (comp_size[a] < comp_size[b]) {
            std::swap(a, b); // Ensure 'a' is the root of the larger component
        }
        parent[b] = a;       // Make 'a' the parent of 'b's root
        comp_size[a] += comp_size[b]; // Update the size of the merged component
    }
}

/**
 * @brief Solves the problem of determining if each edge can be included in an MST.
 *
 * Reads graph input, sorts edges by weight, and uses DSU to determine for each
 * edge if it can be part of a Minimum Spanning Tree.
 */
void solve() {
    int n; // Number of nodes
    int m; // Number of edges
    std::cin >> n >> m;

    // Store all m edges, along with their original input index.
    std::vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        edges[i].original_index = i; // Store the original index
    }

    // Sort edges in ascending order of weight.
    std::sort(edges.begin(), edges.end());

    // Initialize DSU structure
    parent.resize(n + 1); // Nodes are 1-indexed
    std::iota(parent.begin(), parent.end(), 0); // parent[i] = i for all i (each node is its own set)
    comp_size.assign(n + 1, 1); // Each component initially has size 1

    // This vector will store the boolean result for each edge, indexed by its original_index.
    std::vector<bool> can_be_in_mst(m);

    // Iterate through edges, processing them in blocks of equal weight.
    int i = 0;
    while (i < m) {
        int current_weight = edges[i].weight;
        int j = i; // 'j' marks the start of the current block of edges with 'current_weight'

        // First pass: Check all edges in the current weight block without performing unions yet.
        // This ensures that when we check an edge (u,v) of weight W, we only consider paths
        // formed by edges with weight < W.
        while (j < m && edges[j].weight == current_weight) {
            int u_root = find_set(edges[j].u); // Find root of u's component
            int v_root = find_set(edges[j].v); // Find root of v's component

            if (u_root != v_root) {
                // If u and v are in different components, this edge can potentially be in an MST.
                // It means there's no path between u and v using only edges strictly less than current_weight.
                can_be_in_mst[edges[j].original_index] = true;
            } else {
                // If u and v are already in the same component, this edge creates a cycle
                // with edges of strictly smaller weights (or other edges of the same weight
                // already processed in this block that connected these components).
                // Thus, it cannot be in an MST.
                can_be_in_mst[edges[j].original_index] = false;
            }
            j++;
        }

        // Second pass: Perform unions for edges in the current weight block that were marked as true.
        // This updates the DSU structure for the next weight block.
        int k = i;
        while (k < m && edges[k].weight == current_weight) {
            if (can_be_in_mst[edges[k].original_index]) {
                union_sets(edges[k].u, edges[k].v);
            }
            k++;
        }
        i = j; // Move 'i' to the beginning of the next weight block
    }

    // Print the results for each edge in the original input order.
    for (int i = 0; i < m; ++i) {
        if (can_be_in_mst[i]) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
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

