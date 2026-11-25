#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int MAXN = 1e5 + 5;
const int LOG = 20;

int n, q;
int h[MAXN];
int nxt[MAXN];         // Next greater to the right
int P[MAXN][LOG];      // Binary lifting table

void preprocess_nxt_greater() {
    stack<int> st;
    for (int i = n; i >= 1; --i) {
        while (!st.empty() && h[st.top()] <= h[i]) st.pop();
        if (st.empty()) nxt[i] = n + 1;
        else nxt[i] = st.top();
        st.push(i);
    }
}

void build_lift_table() {
    for (int i = 1; i <= n; ++i)
        P[i][0] = nxt[i];
    
    for (int j = 1; j < LOG; ++j)
        for (int i = 1; i <= n; ++i)
            P[i][j] = (P[i][j - 1] <= n ? P[P[i][j - 1]][j - 1] : n + 1);
}

int query(int a, int b) {
    int cnt = 0, pos = a;
    for (int j = LOG - 1; j >= 0; --j) {
        if (P[pos][j] <= b) {
            cnt += (1LL << j);
            pos = P[pos][j];
        }
    }
    return cnt + 1; // include a itself
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> h[i];

    preprocess_nxt_greater();
    build_lift_table();

    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << query(a, b) << endl;
    }
}
