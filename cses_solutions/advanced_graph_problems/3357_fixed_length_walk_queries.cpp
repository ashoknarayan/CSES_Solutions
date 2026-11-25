#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m, q;
    cin >> n >> m >> q;
    
    vector<vector<int>> adj(n + 1);
    adj.reserve(n + 1);
    
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    // Flatten to reduce cache misses
    static int dist[2501][2501][2]; // [start][end][parity]
    memset(dist, -1, sizeof(dist));
    
    // BFS from each node
    for (int start = 1; start <= n; start++) {
        static int d[2501][2];
        memset(d, -1, sizeof(d));
        
        static int que[5001];
        static int parity_que[5001];
        int head = 0, tail = 0;
        
        que[tail] = start;
        parity_que[tail] = 0;
        tail++;
        d[start][0] = 0;
        
        while (head < tail) {
            int u = que[head];
            int par = parity_que[head];
            head++;
            
            for (int v : adj[u]) {
                int new_par = 1 - par;
                if (d[v][new_par] == -1) {
                    d[v][new_par] = d[u][par] + 1;
                    que[tail] = v;
                    parity_que[tail] = new_par;
                    tail++;
                }
            }
        }
        
        // Copy results
        for (int i = 1; i <= n; i++) {
            dist[start][i][0] = d[i][0];
            dist[start][i][1] = d[i][1];
        }
    }
    
    // Process queries
    for (int i = 0; i < q; i++) {
        int a, b, x;
        cin >> a >> b >> x;
        
        int required_dist = dist[a][b][x & 1];
        
        if (required_dist != -1 && required_dist <= x) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
