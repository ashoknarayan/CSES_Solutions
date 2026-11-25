// #ifdef LOCAL
// #define _GLIBCXX_DEBUG 1
// #endif
// =============================================== CODE ================================================ //
#pragma GCC optimize("O3", "unroll-loops")
#include <bits/stdc++.h>
#define F first
#define S second
#define pb push_back
#define pob pop_back
#define all(x) begin(x), end(x)
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#ifdef LOCAL
#define HEHE freopen("in.txt", "r", stdin);
#define debug(HEHE...) std::cerr << "\e[1;31m" << #HEHE << "\033[0m" << " = ", dout(HEHE)
void dout() { std::cerr << "\n"; }
template <typename T, typename... U>
void dout(T t, U... u) { std::cerr << t << ' ', dout(u...); }
#else
#define HEHE ios_base::sync_with_stdio(0), cin.tie(0);
#define debug(...) 7122
#endif
using namespace std;
 
template<typename T1, typename T2>
bool chmin(T1 &a, T2 b) { return a > b ? a = b, 1 : 0; }
template<typename T1, typename T2>
bool chmax(T1 &a, T2 b) { return a < b ? a = b, 1 : 0; }
 
#define pc putchar_unlocked
#define gc readchar
 
inline char readchar() {
    const int S = 1 << 20;  // buffer size
    static char buf[S], *p = buf, *q = buf;
    if (p == q && (q = (p = buf) + fread(buf, 1, S, stdin)) == buf) return EOF;
    return *p++;
}
inline int read(int &x) {
    x = 0;
    char ch = gc(), last = '\0';
    int neg = 1;
    if (ch == EOF) return ch;
    while (ch < '0' or ch > '9') last = ch, ch = gc();
    if (last == '-') neg = -1;
    while (ch >= '0' and ch <= '9') x = x * 10 + ch - '0', ch = gc();
    x *= neg;
    return x;
}
inline void print(int x) {
    static short digits[22], *P;
    if (!x) {
        pc('0');
        return;
    }
    if (x < 0) pc('-'), x = -x;
    P = digits;
    while (x) {
        *P++ = x % 10;
        x /= 10;
    }
    while (P != digits) pc(*(--P) + '0');
}
 
#define ll long long
 
vector<int> is_coin, sum;
int tot;
 
struct linear_lca {
  struct node {
    int d, label, asc;
  };
  vector<node> t;
  vector<int> head;
  linear_lca(const auto& adj) : t(ssize(adj)), head(ssize(t) + 1) {
    vector<pair<int, int>> order;
    auto dfs = [&](auto&& self, int v, int p) -> void {
      sum[v] = is_coin[v];
      int cnt = 0;
      order.emplace_back(v, p);
      t[v].label = ssize(order);
      for (int u : adj[v]) {
        if (u != p) {
          t[u].d = 1 + t[v].d;
          self(self, u, v);
          head[t[u].label] = v;
          sum[v] += sum[u];
          if (sum[u] > 0) cnt++;
          if ((t[u].label & -t[u].label) > (t[v].label & -t[v].label))
          t[v].label = t[u].label;
        }
      }
      if (tot - sum[v] > 0) cnt++;
      if (cnt >= 2) is_coin[v] = 1;
    };
    for (int i = 0; i < ssize(t); i++) {
      if (is_coin[i]) {
        dfs(dfs, i, i); break;
      }
    }
    for (auto [v, p] : order) t[v].asc = t[p].asc | (t[v].label & -t[v].label);
  }
  int lca(int u, int v) {
    if (unsigned j = t[u].label ^ t[v].label; j) {
      j = t[u].asc & t[v].asc & -bit_floor(j);
      if (unsigned k = t[u].asc ^ j; k)
        k = bit_floor(k), u = head[(t[u].label & -k) | k];
      if (unsigned k = t[v].asc ^ j; k)
        k = bit_floor(k), v = head[(t[v].label & -k) | k];
    }
    return t[u].d < t[v].d ? u : v;
  }
  int dist_edges(int u, int v) { return t[u].d + t[v].d - 2 * t[lca(u, v)].d; }
};
 
 
void solve() {
    int n, q; read(n); read(q);
    is_coin.assign(n, 0);
    sum.assign(n, 0);
    FOR (i, 0, n - 1) read(is_coin[i]), tot += is_coin[i];
    vector<vector<int>> adj(n);
    FOR (i, 2, n) {
        int u, v; read(u); read(v);
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    linear_lca ds(adj);
    vector<int> dis(n, -1);
    queue<int> que;
    int ans = 0;
    FOR (i, 0, n - 1) if (is_coin[i]) {
        ans++;
        que.push(i);
        dis[i] = 0;
    }
    while (que.size()) {
        int x = que.front(); que.pop();
        for (int i : adj[x]) {
            if (dis[i] == -1) {
                dis[i] = dis[x] + 1;
                que.push(i);
            }
        }
    }
    ans = ans * 2 - 2;
    while (q--) {
        int u, v; read(u); read(v);
        u--; v--;
        if (!is_coin[ds.lca(u, v)]) {
            print(ans + dis[u] + dis[v]);
        }
        else {
            print(ans + (dis[u] + dis[v]) * 2 - ds.dist_edges(u, v));
        }
        pc('\n');
    }
}
signed main() {
    HEHE
    int t = 1; // cin >> t;
    while (t--) solve();
}
