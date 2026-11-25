#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int MAXN = 100005;
const int MAXM = 200005;
const int LOGN = 18; // log2(MAXN + MAX_BCC_NODES) approx log2(2 * 10^5)

vector<int> adj[MAXN];
int dfs_num[MAXN], dfs_low[MAXN];
int parent_dfs[MAXN];
int timer;
bool is_articulation_point[MAXN];
vector<pair<int, int>> edge_stack; // For BCCs
int bcc_count;
vector<vector<int>> bccs; // Stores vertices for each BCC
vector<int> node_to_bcc_idx[MAXN]; // Stores which BCCs each node belongs to

// For Block-Cut Tree
vector<int> bct_adj[2 * MAXN]; // MAXN for original nodes, MAXN for BCCs
int bct_depth[2 * MAXN];
int bct_parent_lca[LOGN][2 * MAXN];
int bct_node_count;

// Maps original city ID to its corresponding BCT node ID
// If city is AP, it maps to its cut-vertex node.
// If city is not AP, it maps to its unique BCC node.
int city_to_bct_node[MAXN];
// Helper for non-AP cities, maps to their single BCC.
int non_ap_city_to_bcc_id[MAXN]; 

void find_bccs_dfs(int u, int p = -1) {
    dfs_num[u] = dfs_low[u] = timer++;
    parent_dfs[u] = p;

    int children = 0;
    for (int v : adj[u]) {
        if (v == p) continue;

        if (dfs_num[v] != -1) { // Back edge
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
            if (dfs_num[v] < dfs_num[u]) { // To avoid processing edges twice in stack if already processed
                edge_stack.push_back({u, v});
            }
        } else { // Tree edge
            edge_stack.push_back({u, v});
            children++;
            find_bccs_dfs(v, u);
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);

            // If u is root and has >= 2 children, it's an AP
            // If u is not root, and for any child v, low[v] >= num[u], u is an AP
            if ((p != -1 && dfs_low[v] >= dfs_num[u]) || (p == -1 && children > 1)) {
                is_articulation_point[u] = true;

                // Found a new BCC
                bcc_count++;
                bccs.emplace_back();
                set<int> current_bcc_nodes; // Use set to avoid duplicates

                pair<int, int> edge;
                do {
                    edge = edge_stack.back();
                    edge_stack.pop_back();
                    current_bcc_nodes.insert(edge.first);
                    current_bcc_nodes.insert(edge.second);
                } while (!(edge.first == u && edge.second == v) && !(edge.first == v && edge.second == u));

                for (int node : current_bcc_nodes) {
                    bccs.back().push_back(node);
                    node_to_bcc_idx[node].push_back(bcc_count - 1);
                }
            }
        }
    }
}

void build_bct() {
    bct_node_count = 0; // Reset node counter for BCT

    // Assign BCT node IDs for articulation points
    // APs get IDs from 0 to N-1 (original node IDs)
    // BCCs get IDs from N to N + bcc_count - 1
    // This way, city_to_bct_node[i] = i for APs.
    // For BCCs, use bct_node_count to get new IDs
    int ap_bct_start_idx = 1; // We can use original node IDs for APs.
    int bcc_bct_start_idx = MAXN; // Starting index for BCC nodes in BCT

    for (int i = 1; i < MAXN; ++i) {
        if (is_articulation_point[i]) {
            city_to_bct_node[i] = i; // AP nodes in BCT use their original ID
            // Make sure these nodes are actually counted for bct_node_count in the upper range
            // This is handled implicitly by iterating up to MAXN+bcc_count
        }
    }

    for (int i = 0; i < bcc_count; ++i) {
        int bcc_bct_node_id = bcc_bct_start_idx + i;
        
        for (int node_in_bcc : bccs[i]) {
            if (is_articulation_point[node_in_bcc]) {
                // Add edge between AP node and BCC node in BCT
                bct_adj[city_to_bct_node[node_in_bcc]].push_back(bcc_bct_node_id);
                bct_adj[bcc_bct_node_id].push_back(city_to_bct_node[node_in_bcc]);
            } else {
                // For non-AP nodes, map them to their single BCC node
                city_to_bct_node[node_in_bcc] = bcc_bct_node_id;
                non_ap_city_to_bcc_id[node_in_bcc] = i; // Store BCC index for lookup
            }
        }
    }
    
    // Total nodes in BCT for LCA purposes
    bct_node_count = MAXN + bcc_count; 
}


void bct_dfs(int u, int p, int d) {
    bct_depth[u] = d;
    bct_parent_lca[0][u] = p;

    for (int v : bct_adj[u]) {
        if (v == p) continue;
        bct_dfs(v, u, d + 1);
    }
}

void preprocess_lca(int root_bct_node) {
    bct_dfs(root_bct_node, root_bct_node, 0); // Root parent is itself

    for (int k = 1; k < LOGN; ++k) {
        for (int u = 0; u < bct_node_count; ++u) { // Iterate over all possible BCT nodes
            bct_parent_lca[k][u] = bct_parent_lca[k - 1][bct_parent_lca[k - 1][u]];
        }
    }
}

int get_lca(int u, int v) {
    if (bct_depth[u] < bct_depth[v]) swap(u, v);

    for (int k = LOGN - 1; k >= 0; --k) {
        if (bct_depth[u] - (1 << k) >= bct_depth[v]) {
            u = bct_parent_lca[k][u];
        }
    }

    if (u == v) return u;

    for (int k = LOGN - 1; k >= 0; --k) {
        if (bct_parent_lca[k][u] != bct_parent_lca[k][v]) {
            u = bct_parent_lca[k][u];
            v = bct_parent_lca[k][v];
        }
    }
    return bct_parent_lca[0][u];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    cin >> n >> m >> q;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Initialize dfs arrays
    for (int i = 1; i <= n; ++i) {
        dfs_num[i] = -1;
        dfs_low[i] = -1;
        is_articulation_point[i] = false;
        node_to_bcc_idx[i].clear();
    }
    timer = 0;
    bcc_count = 0;
    bccs.clear();
    edge_stack.clear();

    // Find BCCs and APs
    // Assuming the graph is connected, start DFS from node 1
    // If not connected, loop through all nodes for find_bccs_dfs if dfs_num[i] == -1
    find_bccs_dfs(1);
    
    // Handle the last BCC if stack is not empty after main DFS (for cases like single edge graph or cycle)
    if (!edge_stack.empty()) {
        bcc_count++;
        bccs.emplace_back();
        set<int> current_bcc_nodes;
        while (!edge_stack.empty()) {
            pair<int, int> edge = edge_stack.back();
            edge_stack.pop_back();
            current_bcc_nodes.insert(edge.first);
            current_bcc_nodes.insert(edge.second);
        }
        for (int node : current_bcc_nodes) {
            bccs.back().push_back(node);
            node_to_bcc_idx[node].push_back(bcc_count - 1);
        }
    }

    build_bct();
    
    // Find a root for the BCT. It can be any node that exists in the BCT.
    // Since the graph is connected, the BCT will be connected.
    int bct_root = -1;
    for(int i = 1; i <= n; ++i) {
        if (is_articulation_point[i] || !node_to_bcc_idx[i].empty()) { // Check if node maps to a BCT node
            bct_root = city_to_bct_node[i];
            break;
        }
    }
    
    // This case might happen if N=1 or N=2 and it's a single BCC
    if (bct_root == -1 && bcc_count > 0) {
        bct_root = MAXN; // First BCC node
    } else if (bct_root == -1 && n > 0) { // Single node graph, or isolated components - but problem says connected.
         bct_root = 1; // If it's a graph with N=1, no BCCs but node 1 exists.
    }

    if (bct_root != -1) {
        preprocess_lca(bct_root);
    }
    
    for (int i = 0; i < q; ++i) {
        int u, v, c;
        cin >> u >> v >> c;

        if (u == c || v == c) {
            cout << "NO\n";
            continue;
        }
        if (u == v) {
            cout << "YES\n";
            continue;
        }

        if (!is_articulation_point[c]) {
            cout << "YES\n";
            continue;
        }

        // c is an articulation point
        int bct_u = city_to_bct_node[u];
        int bct_v = city_to_bct_node[v];
        int bct_c = city_to_bct_node[c];

        int lca_uv = get_lca(bct_u, bct_v);
        int lca_uc = get_lca(bct_u, bct_c);
        int lca_vc = get_lca(bct_v, bct_c);

        // Check if bct_c is on the path between bct_u and bct_v
        // d(u,v) = d(u,lca(u,v)) + d(v,lca(u,v))
        // d(u,v) = depth[u] + depth[v] - 2*depth[lca(u,v)]
        long long dist_uv = (long long)bct_depth[bct_u] + bct_depth[bct_v] - 2LL * bct_depth[lca_uv];
        long long dist_uc = (long long)bct_depth[bct_u] + bct_depth[bct_c] - 2LL * bct_depth[lca_uc];
        long long dist_vc = (long long)bct_depth[bct_v] + bct_depth[bct_c] - 2LL * bct_depth[lca_vc];

        if (dist_uv == dist_uc + dist_vc) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }

    return 0;
}
