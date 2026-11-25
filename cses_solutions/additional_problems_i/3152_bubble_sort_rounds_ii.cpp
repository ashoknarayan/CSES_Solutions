#include <bits/stdc++.h>
using namespace std;

const int INF32 = 1073741823;
const long long INF64 = 4611686018427387903LL;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int n, k;
vector<int> a;

void ENGINE(int TEST_NUMBER) {
    cin >> n >> k;
    a.resize(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < n; ++i) {
        q.push(a[i]);
        if ((int)q.size() > k) {
            cout << q.top() << ' ';
            q.pop();
        }
    }
    while (!q.empty()) {
        cout << q.top() << ' ';
        q.pop();
    }
    cout << '\n';
}

// Generic Fenwick Tree (Binary Indexed Tree)
template<typename T, typename Op>
struct Fenwick {
    int n;
    vector<T> data;
    Op op;

    Fenwick(int _n, Op _op) : n(_n), data(_n, _op.e()), op(_op) {}

    void apply(int x, T v) {
        while (x < n) {
            data[x] = op.op(data[x], v);
            x |= x + 1;
        }
    }

    T prod(int x) {
        T res = op.e();
        ++x;
        while (x > 0) {
            res = op.op(res, data[x - 1]);
            x &= x - 1;
        }
        return res;
    }
};

// Operation for sum
struct Opt {
    int op(int a, int b) const { return a + b; }
    int e() const { return 0; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // Uncomment to support multiple tests
    // cin >> t;
    for (int i = 1; i <= t; ++i) {
        ENGINE(i);
    }
    return 0;
}
