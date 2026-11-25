#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

int sbi(string s)
{
    int ans = 0;
    reverse(s.begin(), s.end());
    for (int i = 0; i < s.size(); ++i)
        ans += ((s[i] - '0') * (1LL << i));
    return ans;
}

string ibs(int n, int len)
{
    string ans = "";
    while (n != 0)
    {
        int t = n % 2;
        n /= 2;
        ans += '0' + t;
    }
    while (ans.size() < len)
        ans += '0';
    reverse(ans.begin(), ans.end());
    return ans;
}

void dfs(int u, vector<int>& path, vector<vector<int>>& g, vector<bool>& visited)
{
    visited[u] = true;
    for (int v : g[u])
    {
        if (!visited[v])
            dfs(v, path, g, visited);
    }
    path.push_back(u);
}

signed main()
{
    int n;
    cin >> n;
    vector<vector<int>> g((1 << n));
    // Make the graph
    for (int i = 0; i < (1 << n); ++i)
    {
        string s = ibs(i, n);
        s.erase(0, 1);
        g[i].push_back(sbi(s + '0'));
        g[i].push_back(sbi(s + '1'));
    }

    // Find the Hamiltonian path (Eulerian cycle in this case)
    vector<bool> visited(1 << n, false);
    vector<int> path;

    // Start DFS from node 0 (you can start from any node)
    dfs(0, path, g, visited);

    // The path is currently in reverse order due to how DFS finishes, so reverse it
    reverse(path.begin(), path.end());

    // Construct the compressed string from the Hamiltonian path
    string result = ibs(path[0], n);
    for (int i = 1; i < path.size(); ++i)
    {
        result += ibs(path[i], n).back(); // Add only the last bit of each new node
    }

    cout << result << endl;

    return 0;
}
