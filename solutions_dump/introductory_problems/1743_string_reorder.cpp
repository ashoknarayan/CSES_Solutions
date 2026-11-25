#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    string s;
    cin >> s;
    int n = s.size();
    vector<int> freq(26);
    for (char c : s) freq[c - 'A']++;

    string result = "";
    char last = '#'; // dummy initial

    for (int i = 0; i < n; ++i) {
        bool found = false;
        for (int c = 0; c < 26; ++c) {
            if (freq[c] == 0) continue;
            if (last - 'A' == c) continue;

            // Try placing c
            freq[c]--;

            // Check if rest is still possible
            int maxf = *max_element(freq.begin(), freq.end());
            if (maxf <= (n - i - 1 + 1) / 2) {
                result += (char)('A' + c);
                last = 'A' + c;
                found = true;
                break;
            }

            freq[c]++; // undo
        }

        if (!found) {
            cout << "-1\n";
            return 0;
        }
    }

    cout << result << '\n';
}
