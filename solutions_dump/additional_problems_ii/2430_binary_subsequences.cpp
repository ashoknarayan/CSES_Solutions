#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    long long n;
    std::cin >> n;

    std::string best_s = "";

    for (long long c0_s = 0; c0_s <= n; ++c0_s) {
        long long c0 = c0_s;
        long long c1 = n - c0_s;
        std::string s = "";
        bool ok = true;

        while (c0 > 0 || c1 > 0) {
            if (!best_s.empty() && s.length() >= best_s.length()) {
                ok = false;
                break;
            }
            if (c0 == c1 || c0 < 0 || c1 < 0) {
                ok = false;
                break;
            }

            if (c0 > c1) {
                if (c1 == 0) {
                    s.insert(0, c0, '0');
                    c0 = 0;
                } else {
                    if ((c0 - c1) % (c1 + 1) == 0) { ok = false; break; }
                    long long k = (c0 - c1) / (c1 + 1) + 1;
                    s.insert(0, k, '0');
                    c0 -= k * (c1 + 1);
                }
            } else {
                if (c0 == 0) {
                    s.insert(0, c1, '1');
                    c1 = 0;
                } else {
                    if ((c1 - c0) % (c0 + 1) == 0) { ok = false; break; }
                    long long k = (c1 - c0) / (c0 + 1) + 1;
                    s.insert(0, k, '1');
                    c1 -= k * (c0 + 1);
                }
            }
        }

        if (ok && (best_s.empty() || s.length() < best_s.length())) {
            best_s = s;
        }
    }
    std::cout << best_s << std::endl;

    return 0;
}
