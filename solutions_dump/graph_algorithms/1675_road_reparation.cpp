#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define int long long 
struct Edge
{
    int u, v, weight;
    bool operator<(const Edge& other) const
    {
        return weight < other.weight;
    }
};

int find(int u, vector<int>& parent)
{
    if (parent[u] == u)
        return u;
    return parent[u] = find(parent[u], parent);
}

bool unite(int u, int v, vector<int>& parent, vector<int>& rank)
{
    int root_u = find(u, parent);
    int root_v = find(v, parent);
    
    if (root_u != root_v)
    {
        if (rank[root_u] > rank[root_v])
            parent[root_v] = root_u;
        else if (rank[root_u] < rank[root_v])
            parent[root_u] = root_v;
        else
        {
            parent[root_v] = root_u;
            rank[root_u]++;
        }
        return true;
    }
    return false;
}

signed main()
{
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        edges[i].u--;  // Zero-indexing the nodes
        edges[i].v--;
    }

    sort(edges.begin(), edges.end());

    vector<int> parent(n), rank(n, 0);
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
    }

    int mst_weight = 0;
    int edges_used = 0;
    for (const Edge& edge : edges)
    {
        if (unite(edge.u, edge.v, parent, rank))
        {
            mst_weight += edge.weight;
            edges_used++;
        }
    }

    if (edges_used == n - 1)
    {
        cout << mst_weight << endl;
    }
    else
    {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}
