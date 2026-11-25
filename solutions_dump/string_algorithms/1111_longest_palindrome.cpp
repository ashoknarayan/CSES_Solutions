#include <bits/stdc++.h>
using namespace std;

string manacher(string s) {
    int n = s.size();
    string t = "#";
    for (char e : s) t += e, t += '#';

    vector<int> p(t.size());
    int c = 0, r = 0;
    int C = 0, L = 0;

    for (int i = 0; i < t.size(); ++i) {
        int m = 2 * c - i;
        if (r > i) p[i] = min(p[m], r - i);

        int a = i + (p[i] + 1);
        int b = i - (p[i] + 1);
        while (b >= 0 && a < t.size() && t[a] == t[b]) {
            p[i]++;
            ++a;
            --b;
        }

        if (p[i] > L) {
            C = i;
            L = p[i];
        }
        if (i + p[i] > r) {
            c = i;
            r = i + p[i];
        }
    }

    return s.substr((C - L) / 2, L); // Corrected extraction
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    cout << manacher(s) << endl;
    return 0;
}
