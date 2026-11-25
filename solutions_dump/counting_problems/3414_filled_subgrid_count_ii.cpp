#include <iostream>
#include <vector>
#include <string>
#include <utility>

using pii = std::pair<int, int>;
using bsi = std::vector<int>;
using bsl = std::vector<long long>;

struct SNOWFLAKE {
  SNOWFLAKE(int argc, char* argv[], int TEST_NUMBER) {
    int n, m; std::cin >> n >> m;
    std::vector<std::string> a(n);
    for (auto& i : a) std::cin >> i;

    // Convert 'A'.. to 0-based integers
    for (auto& i : a) {
      for (auto& j : i) j -= 'A';
    }

    bsl ans(m, 0); // answer for each character
    std::vector up(n, bsi(n, 0));

    for (int i = 0; i < n; ++i) {
      std::vector<pii> stk;
      int tar = 0;

      for (int j = 0; j < n; ++j) {
        if (i > 0 && a[i][j] == a[i - 1][j]) up[i][j] = up[i - 1][j] + 1;
        else up[i][j] = 1;

        if (j > 0 && a[i][j] != a[i][j - 1]) {
          stk.clear();
          tar = 0;
        }

        int len = 1;
        while (!stk.empty() && stk.back().first >= up[i][j]) {
          tar -= stk.back().first * stk.back().second;
          len += stk.back().second;
          stk.pop_back();
        }

        stk.emplace_back(up[i][j], len);
        tar += up[i][j] * len;
        ans[a[i][j]] += tar;
      }
    }

    for (auto i : ans) std::cout << i << "\n";
  }
};

int main(int argc, char* argv[]) {
  SNOWFLAKE(argc, argv, 1);
  return 0;
}
