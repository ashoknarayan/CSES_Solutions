#include <iostream>
#include <vector>
#include <queue>
#include <limits> // For numeric_limits

using namespace std;

const long long INF = numeric_limits<long long>::max();

// Structure for graph edges
struct Edge {
    int to;
    long long weight;
};

// Custom comparator for priority queue (min-heap)
struct CompareDist {
    bool operator()(const pair<long long, int>& a, const pair<long long, int>& b) {
        return a.first > b.first; // Sort by smallest distance
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<long long> company_costs(m + 1); // 1-indexed for companies
    for (int i = 1; i <= m; ++i) {
        cin >> company_costs[i];
    }

    // Graph representation:
    // Nodes 1 to N are cities.
    // Nodes N+1 to N+M are bus companies.
    // Total nodes: N + M
    vector<vector<Edge>> adj(n + m + 1);

    // Read bus company routes and build graph
    for (int j = 1; j <= m; ++j) { // For each bus company j
        int k_cities;
        cin >> k_cities;
        vector<int> cities_operated_by_company(k_cities);
        for (int p = 0; p < k_cities; ++p) {
            cin >> cities_operated_by_company[p];
        }

        // Add edges:
        // 1. From city to company node (weight 0)
        // 2. From company node to city (weight company_costs[j])
        int company_node_id = n + j;
        for (int city_id : cities_operated_by_company) {
            // Edge from city_id to company_node_id with weight 0
            adj[city_id].push_back({company_node_id, 0});
            // Edge from company_node_id to city_id with weight company_costs[j]
            adj[company_node_id].push_back({city_id, company_costs[j]});
        }
    }

    // Dijkstra's Algorithm
    vector<long long> dist(n + m + 1, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, CompareDist> pq;

    dist[1] = 0; // Syrjälä is city 1
    pq.push({0, 1});

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) {
            continue; // Already found a shorter path
        }

        for (const auto& edge : adj[u]) {
            int v = edge.to;
            long long weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Output the cheapest route costs to cities 1 to N
    for (int i = 1; i <= n; ++i) {
        cout << dist[i] << (i == n ? "" : " ");
    }
    cout << endl;

    return 0;
}
