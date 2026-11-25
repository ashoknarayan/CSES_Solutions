#include <iostream> // Required for input and output operations
#include <vector>   // Although not strictly necessary for this simple solution,
                    // often used in graph problems.
#include <algorithm> // Required for std::min and std::max, though if/else works too.

/**
 * @brief Solves the problem of orienting an undirected graph to be acyclic.
 *
 * This function reads the number of nodes (n) and edges (m), then for each
 * edge (u, v) it reads from input, it directs the edge from the node with the
 * smaller ID to the node with the larger ID. This simple rule guarantees
 * that the resulting directed graph will be acyclic, as no cycle can be formed
 * by strictly increasing node IDs.
 */
void solve() {
    int n; // Number of nodes
    int m; // Number of edges

    // Read the number of nodes and edges from standard input.
    std::cin >> n >> m;

    // Iterate through each of the 'm' edges.
    for (int i = 0; i < m; ++i) {
        int u, v; // Endpoints of the current undirected edge

        // Read the two cities connected by the current road.
        std::cin >> u >> v;

        // Apply the rule: direct the edge from the smaller ID to the larger ID.
        if (u < v) {
            // If u is smaller than v, direct the edge as u -> v.
            std::cout << u << " " << v << "\n";
        } else {
            // If v is smaller than u (or if u == v, though problem states distinct),
            // direct the edge as v -> u.
            std::cout << v << " " << u << "\n";
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
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Call the solver function.
    solve();

    return 0; // Indicate successful execution.
}

