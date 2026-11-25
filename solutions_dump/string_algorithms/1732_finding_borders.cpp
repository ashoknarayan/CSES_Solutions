#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(const string &s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

vector<int> find_borders(const string &s) {
    vector<int> pi = prefix_function(s);
    vector<int> borders;

    // Collect borders using the prefix function values
    int length = pi.back(); // The length of the longest border of the whole string
    while (length > 0) {
        borders.push_back(length);
        length = pi[length - 1]; // Move to the next longest border
    }
    reverse(borders.begin(), borders.end()); // Reverse to have them in the correct order
    return borders;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string s; cin >> s;
    vector<int> borders = find_borders(s);
    for (int border : borders) cout << border << " ";
    cout << endl;
    return 0;
}


// THis is also a part of Z alg
// Also it plays a major role in KMP Alg
