#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int MAX = 2e5 + 5;

int n, m, k;

struct DSU {
    vector<int> parent, rank;
    int components;

    DSU(int n) {
        parent.resize(n+1);
        rank.resize(n+1, 1);
        components = n;
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        int xr = find(x), yr = find(y);
        if (xr == yr) return false;
        if (rank[xr] < rank[yr]) swap(xr, yr);
        parent[yr] = xr;
        if (rank[xr] == rank[yr]) rank[xr]++;
        components--;
        return true;
    }

    int count() {
        return components;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    vector<pair<int,int>> edges(m);
    set<pair<int,int>> broken_set;
    vector<pair<int,int>> broken(k);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);
        edges[i] = {a, b};
    }

    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);
        broken[i] = {a, b};
        broken_set.insert({a, b});
    }

    DSU dsu(n);
    for (auto [a, b] : edges) {
        if (!broken_set.count({a, b}))
            dsu.unite(a, b);
    }

    vector<int> res;
    // Process in reverse
    for (int i = k-1; i >= 0; --i) {
        res.push_back(dsu.count());
        dsu.unite(broken[i].first, broken[i].second);
    }

    reverse(res.begin(), res.end());
    for (int x : res) cout << x << endl;
}
