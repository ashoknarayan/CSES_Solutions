#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int findGirth(int n, vector<vector<int>>& adj) {
    int girth = INF;
    
    // Try BFS from each vertex
    for(int start = 1; start <= n; start++) {
        vector<int> dist(n + 1, INF);
        vector<int> parent(n + 1, -1);
        queue<int> q;
        
        dist[start] = 0;
        q.push(start);
        
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            
            for(int u : adj[v]) {
                // If unvisited, add to queue
                if(dist[u] == INF) {
                    dist[u] = dist[v] + 1;
                    parent[u] = v;
                    q.push(u);
                }
                // If visited and not parent, we found a cycle
                else if(u != parent[v]) {
                    // Cycle length = dist[v] + dist[u] + 1
                    girth = min(girth, dist[v] + dist[u] + 1);
                }
            }
        }
    }
    
    return (girth == INF) ? -1 : girth;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    // Create adjacency list
    vector<vector<int>> adj(n + 1);
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    cout << findGirth(n, adj) << endl;
    
    return 0;
}
