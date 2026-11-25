#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

// Use long long for counts as they can become very large.
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<string> forest(n);
    for (int i = 0; i < n; ++i) {
        cin >> forest[i];
    }

    // Step 1: Precompute the histogram heights (h matrix).
    vector<vector<int>> h(n, vector<int>(m, 0));
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            if (forest[i][j] == '.') {
                h[i][j] = (i == 0) ? 1 : h[i - 1][j] + 1;
            }
        }
    }

    // Step 3 & 4: Use a 3rd-order difference array to accumulate counts.
    // ans_diff3[h][w] stores updates. 
    // 1st diff is w.r.t. h, 2nd and 3rd are w.r.t. w.
    vector<vector<ll>> ans_diff3(n + 2, vector<ll>(m + 3, 0));

    auto add_contribution = [&](int h1, int h2, int w_max) {
        if (h1 > h2) return;
        // For each height h in [h1, h2], we add an arithmetic progression 
        // {w_max, w_max-1, ..., 1} to the counts for widths {1, 2, ..., w_max}.
        // This is done in O(1) via 6 updates to the 3rd-order difference array.

        // Update for column 1
        ans_diff3[h1][1] += w_max;
        ans_diff3[h2 + 1][1] -= w_max;

        // Update for column 2
        ans_diff3[h1][2] -= (w_max + 1);
        ans_diff3[h2 + 1][2] += (w_max + 1);

        // Update for column w_max + 2
        ans_diff3[h1][w_max + 2] += 1;
        ans_diff3[h2 + 1][w_max + 2] -= 1;
    };

    // Step 2: Process each row's histogram.
    for (int i = 0; i < n; ++i) {
        stack<pair<int, int>> s; // pair: {height, start_pos}
        for (int j = 0; j < m; ++j) {
            int current_h = h[i][j];
            int start_pos = j;
            while (!s.empty() && s.top().first >= current_h) {
                int top_h = s.top().first;
                int top_pos = s.top().second;
                s.pop();

                int h_on_stack_below = s.empty() ? 0 : s.top().first;
                int h_lower = max(h_on_stack_below, current_h);

                if (top_h > h_lower) {
                    add_contribution(h_lower + 1, top_h, j - top_pos);
                }
                start_pos = top_pos;
            }
            if (current_h > 0) {
                s.push({current_h, start_pos});
            }
        }

        // Process rectangles extending to the right edge of the grid.
        while (!s.empty()) {
            int top_h = s.top().first;
            int top_pos = s.top().second;
            s.pop();

            int h_on_stack_below = s.empty() ? 0 : s.top().first;

            if (top_h > h_on_stack_below) {
                add_contribution(h_on_stack_below + 1, top_h, m - top_pos);
            }
        }
    }

    // Step 4: Reconstruct the final answer matrix from the difference array.
    vector<vector<ll>>& ans_diff2 = ans_diff3; // Reuse memory
    for (int w = 1; w <= m + 2; ++w) {
        for (int h = 1; h <= n + 1; ++h) {
            ans_diff2[h][w] += ans_diff2[h - 1][w];
        }
    }

    vector<vector<ll>>& ans_diff1 = ans_diff2; // Reuse memory
    for (int h = 1; h <= n + 1; ++h) {
        for (int w = 1; w <= m + 1; ++w) {
            ans_diff1[h][w] += ans_diff1[h][w - 1];
        }
    }

    vector<vector<ll>>& ans = ans_diff1; // Reuse memory
    for (int h = 1; h <= n + 1; ++h) {
        for (int w = 1; w <= m; ++w) {
            ans[h][w] += ans[h][w - 1];
        }
    }

    // Print the result.
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cout << ans[i][j] << (j == m ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
