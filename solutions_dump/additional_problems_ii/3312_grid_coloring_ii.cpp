#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> grid;
const int COLORS = 3;
char avail[3] = {'A', 'B', 'C'};

// Variable ID: (i, j, which of 2 choices) => maps to 0-based var
int get_var(int i, int j, int k) {
    return (i * m + j) * 2 + k;
}

int N; // total number of variables = n*m*2
vector<vector<int>> adj, radj;
vector<bool> used;
vector<int> order, comp;

void add_implication(int u, int v) {
    adj[u].push_back(v);
    radj[v].push_back(u);
}

void add_or(int u, int v) {
    // u OR v == (NOT u -> v) AND (NOT v -> u)
    add_implication(u ^ 1, v);
    add_implication(v ^ 1, u);
}

void dfs1(int u) {
    used[u] = true;
    for (int v : adj[u])
        if (!used[v]) dfs1(v);
    order.push_back(u);
}

void dfs2(int u, int c) {
    comp[u] = c;
    for (int v : radj[u])
        if (comp[v] == -1) dfs2(v, c);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    grid.resize(n);
    for (int i = 0; i < n; ++i) cin >> grid[i];

    vector<vector<char>> color1(n, vector<char>(m)), color2(n, vector<char>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            int idx = 0;
            for (char c : avail) {
                if (c != grid[i][j]) {
                    if (idx == 0) color1[i][j] = c;
                    else color2[i][j] = c;
                    idx++;
                }
            }
        }

    N = n * m * 2;
    adj.resize(2 * N);
    radj.resize(2 * N);

    // Add clauses to ensure each cell picks exactly one of its 2 options
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            int a = get_var(i, j, 0);
            int b = get_var(i, j, 1);
            add_or(a, b); // at least one
            add_or(a ^ 1, b ^ 1); // at most one (i.e., not both)
        }

    // Adjacent cell constraints
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (auto [dx, dy] : vector<pair<int,int>>{{0,1},{1,0}}) {
                int ni = i + dx, nj = j + dy;
                if (ni >= n || nj >= m) continue;
                for (int a = 0; a < 2; ++a) {
                    for (int b = 0; b < 2; ++b) {
                        char c1 = (a == 0 ? color1[i][j] : color2[i][j]);
                        char c2 = (b == 0 ? color1[ni][nj] : color2[ni][nj]);
                        if (c1 == c2) {
                            int u = get_var(i, j, a);
                            int v = get_var(ni, nj, b);
                            add_or(u ^ 1, v ^ 1); // Not both u and v
                        }
                    }
                }
            }
        }
    }

    // Kosaraju's algorithm for 2-SAT
    used.assign(2 * N, false);
    for (int i = 0; i < 2 * N; ++i)
        if (!used[i]) dfs1(i);

    comp.assign(2 * N, -1);
    int cid = 0;
    reverse(order.begin(), order.end());
    for (int u : order)
        if (comp[u] == -1) dfs2(u, cid++);

    for (int i = 0; i < N; ++i) {
        if (comp[i * 2] == comp[i * 2 + 1]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    // Assign values
    vector<string> final(n, string(m, '?'));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            int v = get_var(i, j, 0);
            final[i][j] = (comp[v] > comp[v ^ 1] ? color1[i][j] : color2[i][j]);
        }

    for (string& row : final) cout << row << '\n';
}
