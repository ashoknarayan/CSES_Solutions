#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

struct Move {
    string action;
    int amount;
};

int gcd(int a, int b) {
    while (b) tie(a, b) = make_pair(b, a % b);
    return a;
}

pair<vector<Move>, int> simulate(int a, int b, int x, bool ab) {
    // ab == true  -> A to B
    // ab == false -> B to A
    int A = 0, B = 0;
    vector<Move> moves;
    int moved = 0;

    while (true) {
        if (A == x) break;
        if (ab) {
            if (A == 0) {
                A = a;
                moves.push_back({"FILL A", a});
                moved += a;
            } else if (B == b) {
                B = 0;
                moves.push_back({"EMPTY B", b});
                moved += b;
            } else {
                int transfer = min(A, b - B);
                A -= transfer;
                B += transfer;
                moves.push_back({"MOVE A B", transfer});
                moved += transfer;
            }
        } else {
            if (B == 0) {
                B = b;
                moves.push_back({"FILL B", b});
                moved += b;
            } else if (A == a) {
                A = 0;
                moves.push_back({"EMPTY A", a});
                moved += a;
            } else {
                int transfer = min(B, a - A);
                B -= transfer;
                A += transfer;
                moves.push_back({"MOVE B A", transfer});
                moved += transfer;
            }
        }

        if (A == x) break;
        if (moves.size() > 10000) break; // failsafe
    }

    return {moves, moved};
}

void solve() {
    int a, b, x;
    cin >> a >> b >> x;

    if (x > a || x % gcd(a, b) != 0) {
        cout << -1 << endl;
        return;
    }

    auto [moves1, cost1] = simulate(a, b, x, true);  // A->B
    auto [moves2, cost2] = simulate(a, b, x, false); // B->A

    if (cost1 <= cost2) {
        cout << moves1.size() << " " << cost1 << endl;
        for (auto& [act, amt] : moves1) cout << act << endl;
    } else {
        cout << moves2.size() << " " << cost2 << endl;
        for (auto& [act, amt] : moves2) cout << act << endl;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}
