#include <iostream> // Required for input and output operations
#include <vector>   // Required for std::vector (adjacency list, visited, tin, low arrays)
#include <algorithm> // Required for std::min (used in low-link value calculation)
#include <tuple> // Not directly used in final code, but useful for structured data like original_edges_with_idx

// Global variables to be used across DFS calls
std::vector<int> tin;        // Stores the discovery time (time of first visit) for each node
std::vector<int> low;        // Stores the lowest discovery time reachable from a node 'u'
                             // (including 'u' itself) through 'u's subtree and at most one back-edge.
std::vector<bool> visited;   // Tracks if a node has been visited during the current DFS traversal
int timer;                   // A global counter for assigning discovery times
bool has_bridges;            // Flag that becomes true if any bridge is detected in the graph

// Adjacency list representation of the graph.
// Each entry adj[u] contains pairs {v, edge_idx}, where 'v' is a neighbor of 'u'
// and 'edge_idx' is the 0-based index of the original edge {u, v} as read from input.
std::vector<std::vector<std::pair<int, int>>> adj;

// Stores the original undirected edges as read from input.
// This is added to fix the compilation error.
std::vector<std::pair<int, int>> original_edges;

// Stores the final directed edges.
// `final_directed_edges[i]` will hold the directed version of `original_edges[i]`.
std::vector<std::pair<int, int>> final_directed_edges;

/**
 * @brief Performs a Depth First Search to check if the graph is connected.
 *
 * This function is used as a preliminary check. A graph must be connected
 * to be strongly connected. It marks visited nodes.
 *
 * @param u The current node being visited.
 */
void dfs_connectivity(int u) {
    visited[u] = true;
    for (auto& edge : adj[u]) {
        int v = edge.first; // Get the neighbor node
        if (!visited[v]) {
            dfs_connectivity(v); // Recurse if neighbor is not visited
        }
    }
}

/**
 * @brief Performs a Depth First Search to orient edges and detect bridges.
 *
 * This function implements Tarjan's bridge-finding algorithm. As it traverses the graph,
 * it determines the direction of edges for a strong connectivity orientation.
 * If a bridge is found, it indicates that the graph cannot be strongly connected.
 *
 * @param u The current node being visited.
 * @param p_idx The index of the edge that connects 'u' to its parent in the DFS tree.
 * This is used to avoid traversing back immediately to the parent.
 */
void dfs_orient(int u, int p_idx = -1) {
    visited[u] = true;         // Mark current node 'u' as visited
    tin[u] = low[u] = timer++; // Set discovery time and initial low-link value for 'u'

    // Iterate over all neighbors 'v' of 'u'
    for (auto& edge_info : adj[u]) {
        int v = edge_info.first;   // Neighbor node
        int edge_idx = edge_info.second; // Original index of the edge {u, v}

        if (edge_idx == p_idx) { // If this is the edge leading back to the parent in DFS tree
            continue;            // Skip it to avoid infinite recursion / trivial cycle
        }

        if (visited[v]) { // If neighbor 'v' has already been visited
            // This edge (u, v) is either a back-edge (to an ancestor) or a cross-edge.
            // Update low-link value of 'u' based on 'v's discovery time.
            low[u] = std::min(low[u], tin[v]);

            // If 'v' was discovered before 'u' (tin[v] < tin[u]), it means 'v' is an
            // ancestor of 'u' or in a different branch visited earlier.
            // In this case, we direct the edge from 'u' to 'v'. This creates a cycle
            // necessary for strong connectivity.
            // We ensure that we only set the direction for this edge once.
            // If tin[v] < tin[u], this edge (u,v) acts as a back-edge relative to 'u'.
            // If tin[v] > tin[u], then 'v' was processed after 'u' but not as a child of 'u' via a tree edge.
            // In this case, (v, u) would have been directed v -> u when 'v' was processed.
            // So, we only set the direction here if it's a 'backward' going edge relative to discovery times.
            if (tin[v] < tin[u]) {
                final_directed_edges[edge_idx] = {u, v};
            }
        } else { // If neighbor 'v' has not been visited (this is a tree edge)
            final_directed_edges[edge_idx] = {u, v}; // Direct tree edge from parent 'u' to child 'v'
            dfs_orient(v, edge_idx); // Recursively call DFS on child 'v'

            // After returning from the recursive call, update 'u's low-link value.
            // 'u' can reach any node that 'v' can reach, specifically the lowest 'tin' reachable from 'v'.
            low[u] = std::min(low[u], low[v]);

            // Bridge detection condition:
            // If the lowest discovery time reachable from 'v' (low[v]) is greater than
            // the discovery time of 'u' (tin[u]), it means there is no back-edge from
            // 'v's subtree that connects to 'u' or any of 'u's ancestors.
            // Therefore, the edge (u, v) is a bridge.
            if (low[v] > tin[u]) {
                has_bridges = true; // Set the flag indicating a bridge is found
                return;             // No need to continue, as solution is impossible
            }
        }
        // If a bridge was found in a deeper recursion, propagate the flag up.
        if (has_bridges) return;
    }
}

/**
 * @brief Main function to solve the graph orientation problem.
 *
 * Reads graph input, performs connectivity check, then a bridge-detecting DFS
 * to orient edges for strong connectivity. Prints the directed edges or
 * "IMPOSSIBLE" if a strongly connected orientation is not possible.
 */
void solve() {
    int n, m; // n: number of nodes, m: number of edges
    std::cin >> n >> m;

    adj.resize(n + 1); // Resize adjacency list for 1-indexed nodes
    original_edges.resize(m); // Resize to store original edges
    final_directed_edges.resize(m); // Resize to store final oriented edges

    // Read all edges and populate the adjacency list and original_edges array.
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back({v, i}); // Add edge (v, with index i) to u's list
        adj[v].push_back({u, i}); // Add edge (u, with index i) to v's list (bidirectional)
        original_edges[i] = {u, v}; // Store the original undirected edge
    }

    // --- Step 1: Connectivity Check ---
    // Re-initialize visited array for this check.
    visited.assign(n + 1, false);
    int connected_components = 0;
    // Iterate through all nodes to find all connected components.
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs_connectivity(i);
            connected_components++;
        }
    }

    // A graph can only be strongly connected if it has exactly one connected component.
    // Also, a single node (n=1) with no edges (m=0) is trivially strongly connected.
    if (connected_components > 1 || (n == 1 && m > 0) ) { // If n=1 and m>0, it implies self loop or parallel edges, which are not allowed per simple graph assumption.
        std::cout << "IMPOSSIBLE\n";
        return;
    }
    // If n=1 and m=0, no edges to print.
    if (n == 1 && m == 0) {
        return;
    }

    // --- Step 2: Bridge Detection and Edge Orientation ---
    // Re-initialize global variables for the bridge detection DFS.
    visited.assign(n + 1, false); // Reset visited status for the new DFS
    tin.assign(n + 1, 0);         // Reset discovery times
    low.assign(n + 1, 0);         // Reset low-link values
    timer = 0;                    // Reset timer
    has_bridges = false;          // Reset bridge flag

    // Start DFS from node 1 (since we've already confirmed graph is connected,
    // all nodes will be reached from node 1).
    dfs_orient(1); 

    // After DFS, check if any bridge was found.
    // If has_bridges is true, it's impossible to make the graph strongly connected.
    if (has_bridges) {
        std::cout << "IMPOSSIBLE\n";
        return;
    }

    // If no bridges were found, the graph can be strongly connected.
    // Print the directed edges stored in final_directed_edges, which were
    // populated during the dfs_orient traversal. They are ordered by their
    // original input index.
    for (int i = 0; i < m; ++i) {
        std::cout << final_directed_edges[i].first << " " << final_directed_edges[i].second << "\n";
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

