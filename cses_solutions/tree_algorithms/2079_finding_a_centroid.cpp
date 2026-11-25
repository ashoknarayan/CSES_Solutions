#include<bits/stdc++.h>
using namespace std;
#define SZ 200005

vector<int> adj[SZ];
int sub[SZ], n;

void dfs_sub(int u, int p) {
    sub[u]=1;
    for(int v: adj[u]) {
        if(v!=p) {
            dfs_sub(v, u);
            sub[u] += sub[v];
        }
    }
}

int centroid(int u, int p) {
    for(int v: adj[u]) {
        if(v!=p) {
            if(sub[v]>n/2) {
                return centroid(v, u);
            }
        }
    }
    return u;
}

int main() {
    ios::sync_with_stdio(0);
    int u, v;
    cin >> n;

    for(int i=1; i<=n-1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs_sub(1, -1);
    cout << centroid(1, -1);
}

/*!
Centroid of the tree
*/
