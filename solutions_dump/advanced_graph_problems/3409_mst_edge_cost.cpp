#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // For std::iota (optional, good for initializing DSU parent array)

// Constants
const int MAXN = 100005; // Maximum number of nodes
const int MAX_LOGN = 18; // ceil(log2(MAXN)) for binary lifting (log2(10^5) approx 16.6)

// Structure to represent an edge
struct Edge {
    int u, v, w, original_idx;
};

// --- Disjoint Set Union (DSU) Structure ---
struct DSU {
    std::vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        std::iota(parent.begin(), parent.end(), 0); // Initialize parent[i] = i
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};

// --- Binary Lifting for LCA and Max Edge Weight on Path ---
std::vector<std::pair<int, int>> adj_mst[MAXN]; // Adjacency list for the MST
int depth[MAXN];
int up[MAX_LOGN][MAXN];       // up[k][u] is the 2^k-th ancestor of u
int max_val[MAX_LOGN][MAXN];  // max_val[k][u] is max edge weight on path from u to up[k][u]

// DFS to build depth, direct parent, and max edge to parent
void dfs_lca(int u, int p, int d, int edge_w) {
    depth[u] = d;
    up[0][u] = p;
    max_val[0][u] = edge_w;

    for (auto& edge : adj_mst[u]) {
        int v = edge.first;
        int w = edge.second;
        if (v == p) continue;
        dfs_lca(v, u, d + 1, w);
    }
}

// Function to get max edge weight on path between u and v in MST
int getMaxWeightOnPath(int u, int v) {
    int max_w = 0;

    // Bring u and v to the same depth
    if (depth[u] < depth[v]) std::swap(u, v);

    for (int k = MAX_LOGN - 1; k >= 0; --k) {
        if (depth[u] - (1 << k) >= depth[v]) {
            max_w = std::max(max_w, max_val[k][u]);
            u = up[k][u];
        }
    }

    // If v is an ancestor of u, u is now at v's depth. The path is u to v.
    // max_w already has the maximum from u up to v's depth.
    if (u == v) return max_w;

    // Move u and v up until their parents are the same (i.e., just below LCA)
    for (int k = MAX_LOGN - 1; k >= 0; --k) {
        if (up[k][u] != up[k][v]) {
            max_w = std::max({max_w, max_val[k][u], max_val[k][v]});
            u = up[k][u];
            v = up[k][v];
        }
    }
    // Now u and v are children of their LCA. Take max of edges to their LCA.
    max_w = std::max({max_w, max_val[0][u], max_val[0][v]});

    return max_w;
}

// --- Main Function ---

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    std::cin >> n >> m;

    std::vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].original_idx = i;
    }

    // Sort edges by weight for Kruskal's algorithm
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    DSU dsu(n);
    long long global_mst_cost = 0;
    std::vector<bool> is_in_mst(m, false); // Keep track of edges in the global MST

    // Store results, indexed by original_idx
    std::vector<long long> ans(m);

    // Run Kruskal's Algorithm to find the global MST
    for (const auto& edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            global_mst_cost += edge.w;
            is_in_mst[edge.original_idx] = true;
            
            // Add this edge to the MST adjacency list for binary lifting
            adj_mst[edge.u].push_back({edge.v, edge.w});
            adj_mst[edge.v].push_back({edge.u, edge.w});
        }
    }

    // Initialize all answers to global_mst_cost (for edges that are already in MST)
    for (int i = 0; i < m; ++i) {
        ans[i] = global_mst_cost;
    }

    // --- Precompute for Binary Lifting ---
    // Root the MST at node 1 (arbitrarily)
    dfs_lca(1, 0, 0, 0); // Node 0 is a dummy parent for root, edge_w to dummy parent is 0

    // Fill the binary lifting tables
    for (int k = 1; k < MAX_LOGN; ++k) {
        for (int i = 1; i <= n; ++i) {
            up[k][i] = up[k - 1][up[k - 1][i]];
            max_val[k][i] = std::max(max_val[k - 1][i], max_val[k - 1][up[k - 1][i]]);
        }
    }

    // --- Calculate costs for non-MST edges ---
    for (const auto& edge : edges) {
        if (!is_in_mst[edge.original_idx]) {
            // For a non-MST edge (u, v) with weight w, the cost is:
            // C_global - (max weight edge on path between u,v in MST) + w
            int max_w_on_path = getMaxWeightOnPath(edge.u, edge.v);
            ans[edge.original_idx] = global_mst_cost - max_w_on_path + edge.w;
        }
    }

    // Print results in original input order
    for (int i = 0; i < m; ++i) {
        std::cout << ans[i] << "\n";
    }

    return 0;
}
