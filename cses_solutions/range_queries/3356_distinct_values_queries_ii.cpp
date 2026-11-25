#include <bits/stdc++.h>
#include <iterator> // For std::prev and std::next
using namespace std;

#define int long long
#define endl '\n'

const int INF = 1e18;
const int MAXN = 2e5 + 5;

int n, q;
int x[MAXN], P[MAXN];
map<int, set<int>> index_map;

int seg[4 * MAXN];

void build(int id, int l, int r) {
    if (l == r) {
        seg[id] = P[l];
        return;
    }
    int mid = (l + r) / 2;
    build(id*2, l, mid);
    build(id*2+1, mid+1, r);
    seg[id] = min(seg[id*2], seg[id*2+1]);
}

void update(int id, int l, int r, int pos, int val) {
    if (l == r) {
        seg[id] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(id*2, l, mid, pos, val);
    else update(id*2+1, mid+1, r, pos, val);
    seg[id] = min(seg[id*2], seg[id*2+1]);
}

int query(int id, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return INF;
    if (ql <= l && r <= qr) return seg[id];
    int mid = (l + r) / 2;
    return min(query(id*2, l, mid, ql, qr),
               query(id*2+1, mid+1, r, ql, qr));
}

void update_val(int k, int u) {
    int old = x[k];
    if (old == u) return;

    auto& s_old = index_map[old];
    auto it = s_old.find(k);
    int prev = (it == s_old.begin()) ? -1 : *std::prev(it);
    int nxt = std::next(it) == s_old.end() ? -1 : *std::next(it);
    s_old.erase(it);

    if (prev != -1) {
        P[prev] = (nxt == -1 ? INF : nxt);
        update(1, 1, n, prev, P[prev]);
    }

    if (nxt != -1) {
        P[k] = INF;
        update(1, 1, n, nxt, P[nxt]);
    }

    x[k] = u;
    auto& s_new = index_map[u];
    s_new.insert(k);
    auto it2 = s_new.find(k);
    int pre = (it2 == s_new.begin()) ? -1 : *std::prev(it2);
    int nex = std::next(it2) == s_new.end() ? -1 : *std::next(it2);

    if (pre != -1) {
        P[pre] = k;
        update(1, 1, n, pre, P[pre]);
    }

    P[k] = (nex == -1 ? INF : nex);
    update(1, 1, n, k, P[k]);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        index_map[x[i]].insert(i);
    }

    for (auto& [val, pos_set] : index_map) {
        vector<int> pos(pos_set.begin(), pos_set.end());
        for (int i = 0; i < (int)pos.size(); i++) {
            int idx = pos[i];
            if (i + 1 < (int)pos.size())
                P[idx] = pos[i + 1];
            else
                P[idx] = INF;
        }
    }

    build(1, 1, n);

    while (q--) {
        int type, a, b;
        cin >> type >> a >> b;
        if (type == 1) {
            update_val(a, b);
        } else {
            int minP = query(1, 1, n, a, b);
            if (minP <= b) cout << "NO" << endl;
            else cout << "YES" << endl;
        }
    }
}
